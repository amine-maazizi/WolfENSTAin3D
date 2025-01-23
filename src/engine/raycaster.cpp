#include <engine/raycaster.hpp>


SDL_Surface* ConvertImageToRGBA32(SDL_Surface* surface, const char* filename) {
    switch (surface->format->format) {
        case SDL_PIXELFORMAT_RGB24: {
            printf("Conversion de %s de RGB24 vers ARGB8888\n", filename);
            SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB8888, 0);
            if (!converted) {
                printf("Erreur : Impossible de convertir %s : %s\n", filename, SDL_GetError());
                return nullptr;
            }
            SDL_FreeSurface(surface);
            surface = converted;
            break;
        }

        case SDL_PIXELFORMAT_ABGR8888: {
            printf("Traitement de %s avec ABGR8888 pour correspondre a RGBA8888\n", filename);
            uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
            int pixelCount = surface->w * surface->h;

            for (int i = 0; i < pixelCount; ++i) {
                uint8_t* color = reinterpret_cast<uint8_t*>(&pixels[i]);
                uint8_t temp = color[0];
                color[0] = color[2];
                color[2] = temp;
                }
            break;
        }

        default: {
            printf("Conversion de %s de %s vers RGBA32\n", filename, SDL_GetPixelFormatName(surface->format->format));
            SDL_Surface* converted = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
            if (!converted) {
                printf("Erreur : Impossible de convertir %s : %s\n", filename, SDL_GetError());
                return nullptr;
            }
            SDL_FreeSurface(surface);
            surface = converted;
            break;
        }
    }

    return surface;
}


// charge un PNG et transfers ses pixels au vecteur de textures
bool loadTextureFromPNG(const char* filename, std::vector<int>& textureVector) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        printf("Echec de chargement de l'image, erreur: %s\n", IMG_GetError());
        return false;
    }

    if (surface->w != TEX_WIDTH || surface->h != TEX_HEIGHT) {
        printf("Dimensions de l'image dans le chemin %s ne sont pas 64x64\n", filename);
        SDL_FreeSurface(surface);
        return false;
    }

    // Convert image format
    SDL_Surface* convertedSurface = ConvertImageToRGBA32(surface, filename);
    if (!convertedSurface) {
        SDL_FreeSurface(surface);
        return false;
    }
    surface = convertedSurface;

    textureVector.clear();
    textureVector.reserve(TEX_WIDTH * TEX_HEIGHT);

    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    for (int i = 0; i < TEX_WIDTH * TEX_HEIGHT; ++i) {
        textureVector.push_back(static_cast<int>(pixels[i]));
    }

    SDL_FreeSurface(surface);
    return true;
}

Raycaster::Raycaster(Camera& cam) {
    // Redimensionnement des tableaux de textures
    for (int i = 0; i < TEXTURE_NUMBER; i++) {
        texture[i].resize(TEX_WIDTH * TEX_HEIGHT);
    }

    // Initialisation du buffer
    buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; // Contiguous memory allocation
    std::fill(buffer, buffer + (SCREEN_WIDTH * SCREEN_HEIGHT), 0); 

   

    for (int i = 0; i < TEXTURE_NUMBER; i++) {
        if (!loadTextureFromPNG(texPaths[i], texture[i])) {
            printf("Echec dans le chargmeent de la texture %d dont le chemin %s\n", i, texPaths[i]);
            IMG_Quit();
            SDL_Quit();
            exit(1);
        }
    }
}

Raycaster::~Raycaster() {
    // Deallocation
    delete[] buffer;
}

void Raycaster::castRays(Camera& cam, int worldMap[][MAP_WIDTH], BillboardManager& bbManager) {
    // FLOOR CASTING
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        Vector2D<float> rayDir0 =  static_cast<Vector2D<float>>(cam.direction) -  static_cast<Vector2D<float>>(cam.plane);
        Vector2D<float> rayDir1 =  static_cast<Vector2D<float>>(cam.direction) + static_cast<Vector2D<float>>(cam.plane);

        // on centre la coordonnée y
        int p = y - SCREEN_HEIGHT / 2;

        // position verticale de la camera
        float posZ = 0.5f * SCREEN_HEIGHT;

        if (p == 0) continue;

        // distance horizontal entre camera et sol pour y
        float rowDist = posZ / p;

        // pas pour chaque x
        Vector2D<float> floorStep = (rayDir1 - rayDir0) * rowDist * (1.0f / SCREEN_WIDTH);
        Vector2D<float> floor = static_cast<Vector2D<float>>(cam.position) + rayDir0 * rowDist;


        for (int x = 0; x < SCREEN_WIDTH; x++) {
            Vector2D<int> cellCoord(
                (int)floor.getX(),
                (int)floor.getY()
            );

            Vector2D<int> texCoord(
                (int)(TEX_WIDTH * (floor.getX() - cellCoord.getX())) & (TEX_WIDTH - 1),
                (int)(TEX_HEIGHT * (floor.getY() - cellCoord.getY())) & (TEX_HEIGHT - 1)
            );

            floor = floor + floorStep;

            int floorTex = 5;
            int ceilTex = 6;

            // sol
            Uint32 color = texture[floorTex][TEX_WIDTH * texCoord.getY() + texCoord.getX()];
            color = (color >> 1) & 8355711; // ombre
            buffer[y * SCREEN_WIDTH + x] = color;

            // ceilling
            color = texture[ceilTex][TEX_WIDTH * texCoord.getY() + texCoord.getX()];
            color = (color >> 1) & 8355711; // ombre
            buffer[(SCREEN_HEIGHT - y - 1) * SCREEN_WIDTH + x] = color;
        }
    }


    // Parcourir chaque colonne verticale de l'écran
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calcul de la direction du rayon en x
        double cameraX = 2.0 * x / SCREEN_WIDTH - 1.0; // [-1, 1]
        Vector2D<double> rayDir(
            cam.direction.getX() + cam.plane.getX() * cameraX,
            cam.direction.getY() + cam.plane.getY() * cameraX
        );

        ////////// ALGORITHME DDA //////////
        // La cellule où se trouve le rayon à cet instant
        Vector2D<int> map(
            cam.position.getX(),
            cam.position.getY()
        );

        // Longueur du rayon suivant les directions x et y
        Vector2D<double> sideDist;

        // Longueur du rayon de la position actuelle à la prochaine intersection
        Vector2D<double> deltaDist(
            (rayDir.getX() == 0) ? 1e30 : std::abs(1 / rayDir.getX()),
            (rayDir.getY() == 0) ? 1e30 : std::abs(1 / rayDir.getY())
        );

        // Distance perpendiculaire au mur
        double perpWallDist;

        // Direction du pas suivant en x ou y (+1 ou -1)
        Vector2D<int> step;

        // Calcul des valeurs initiales
        if (rayDir.getX() < 0) {
            step.setX(-1);
            sideDist.setX((cam.position.getX() - map.getX()) * deltaDist.getX());
        } else {
            step.setX(1);
            sideDist.setX((map.getX() + 1.0 - cam.position.getX()) * deltaDist.getX());
        }
        if (rayDir.getY() < 0) {
            step.setY(-1);
            sideDist.setY((cam.position.getY() - map.getY()) * deltaDist.getY());
        } else {
            step.setY(1);
            sideDist.setY((map.getY() + 1.0 - cam.position.getY()) * deltaDist.getY());
        }

        // Application de l'algorithme DDA
        int hit = 0;
        bool wasHorizontal; // Type de collision (horizontale ou verticale)
        while (hit == 0) {
            // Saut vers la prochaine cellule
            if (sideDist.getX() < sideDist.getY()) {
                sideDist.setX(sideDist.getX() + deltaDist.getX());
                map.setX(map.getX() + step.getX());
                wasHorizontal = true; // Collision horizontale
            } else {
                sideDist.setY(sideDist.getY() + deltaDist.getY());
                map.setY(map.getY() + step.getY());
                wasHorizontal = false; // Collision verticale
            }

            // Vérifier si le rayon a touché un mur
            if (worldMap[map.getX()][map.getY()] > 0) hit = 1;
        }

        // Calcul de la distance perpendiculaire au mur
        if (wasHorizontal) perpWallDist = (sideDist.getX() - deltaDist.getX());
        else perpWallDist = (sideDist.getY() - deltaDist.getY());

        // Numéro de la texture à utiliser
        int texNum = worldMap[map.getX()][map.getY()] - 1;

        // wallX correspond à l'endroit exact où le mur a été touché
        double wallX;
        if (wasHorizontal) wallX = cam.position.getY() + perpWallDist * rayDir.getY();
        else               wallX = cam.position.getX() + perpWallDist * rayDir.getX();
        wallX -= floor(wallX);

        // Coordonnée X de la texture
        int texX = int(wallX * (double)TEX_WIDTH);
        if ((wasHorizontal && rayDir.getX() > 0) || (!wasHorizontal && rayDir.getY() < 0)) {
            texX = TEX_WIDTH - texX - 1;
        }

        // Calcul de la hauteur de la ligne
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        // Déterminer le début et la fin de la ligne à dessiner
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        // Remplissage de la bande verticale
        double stripe_step = (double)TEX_HEIGHT / lineHeight;
        double texPos = (double)(drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * stripe_step;
        for (int y = drawStart; y < drawEnd; y++) {
            int texY = (int)texPos & (TEX_HEIGHT - 1);
            texPos += stripe_step;
            Uint32 color = texture[texNum][TEX_HEIGHT * texY + texX];
            if (!wasHorizontal) color = (color >> 1) & 8355711; // Assombrir pour les ombres
            buffer[y * SCREEN_WIDTH + x] = color;
            bbManager.ZBuffer.push_back(perpWallDist);
            }
    }

    // BILLBOARD CASTING
    for (int i = 0; i < bbManager.number; i++) {
        // position relative du billboard
        Vector2D<double> relPos = bbManager.billboards[i]->position - cam.position;

        // Transformer le billboard avec l'inverse de la transformation de la camera
        // TODO: usage d'une matrice de transformation est beacoup mieux ici
        // TODO: penser soit ajouter GLM soit definire ma propre class Matrice 2x2 vue que je travaille en 2D
        double invDet = 1.0 / (cam.plane.getX() * cam.direction.getY() - cam.direction.getX() * cam.plane.getY());

        Vector2D<double> transform = Vector2D<double>(
            cam.direction.getY() * relPos.getX() - cam.direction.getX() * relPos.getY(),
            - cam.plane.getY() * relPos.getX() + cam.plane.getX() * relPos.getY()
        ) * invDet;

        int bbScreenX = (int)(SCREEN_WIDTH / 2 * (1 + transform.getX() / transform.getY()));

        // Hauteur du billboard par rapport à l'écran
        int bbHeight = abs((int)(SCREEN_HEIGHT / transform.getY())); // auteur transformée au lieu de la dist reél pour eviter l'effet 'Fisheye'

        // Repratition verticale du sprite
        int drawStartY = -bbHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStartY < 0) drawStartY = 0;
        int drawEndY = bbHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEndY >= SCREEN_HEIGHT) drawEndY = SCREEN_HEIGHT - 1;
        
        // Epaisseur horizontal
        int bbWidth = abs((int)(SCREEN_HEIGHT / transform.getY()));
        int drawStartX = - bbWidth / 2 + bbScreenX;
        if (drawStartX < 0) drawStartX = 0;
        int drawEndX = bbWidth / 2 + bbScreenX;
        if (drawEndX >= SCREEN_WIDTH) drawEndX = SCREEN_WIDTH - 1;

        // insertion dans le buffer
        for (int stripe = drawStartX; stripe < drawEndX; stripe++) {
            // int texX = (int)((stripe - (-bbWidth / 2 + bbScreenX)) * TEX_WIDTH / bbWidth) / 256;
            int texX = (stripe - (-bbWidth / 2 + bbScreenX)) * TEX_WIDTH / bbWidth;

            // On va stocker le sprite dans le buffer du rendering si et seulement si
            // il est devant la  camera
            // il est sur l'écran 
            // Zbuffer + perp Dist
            if (transform.getY() > 0 && stripe > 0 && stripe < SCREEN_WIDTH && transform.getY() < bbManager.ZBuffer[stripe] * 2.0) 
            for (int y = drawStartY; y < drawEndY; y++) { // pour tous pixel dans le stripe 
                int d = y * 256 - SCREEN_HEIGHT * 128 + bbHeight * 128; // les facteurs sont pour eviter floats
                int texY = (d * TEX_HEIGHT) / (bbHeight * 256);
                Uint32 color = texture[bbManager.billboards[bbManager.billboardOrder[i]]->texID][TEX_WIDTH * texY + texX];
                if ((color & 0xFF000000) != 0) buffer[y * SCREEN_WIDTH + stripe] = color;
            }
        }
    }
}

void Raycaster::render(SDL_Renderer* renderer, SDL_Texture* bufferTex) {
    SDL_UpdateTexture(bufferTex, nullptr, buffer, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderCopy(renderer, bufferTex, nullptr, nullptr);

    // nettoyer le buffer
    std::fill(buffer, buffer + (SCREEN_WIDTH * SCREEN_HEIGHT), 0);
}


