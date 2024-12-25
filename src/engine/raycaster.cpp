#include <engine/raycaster.hpp>

// Raycaster::Raycaster() {
//     Redimensionnement des tableaux de textures
//     for (int i = 0; i < 8; i++) {
//         texture[i].resize(TEX_WIDTH * TEX_HEIGHT);
//     }

//     // Initialisation du buffer
//     buffer[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};


//     // Génération de textures selon des motifs
//     for (int x = 0; x < TEX_WIDTH; x++) {
//         for (int y = 0; y < TEX_HEIGHT; y++) {
//             int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
//             int ycolor = y * 256 / TEX_HEIGHT;
//             int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;

//             texture[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); // Texture rouge unie avec croix noire
//             texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;    // Dégradé en nuances de gris
//             texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor;             // Dégradé jaune incliné
//             texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // Dégradé XOR en nuances de gris
//             texture[4][TEX_WIDTH * y + x] = 256 * xorcolor;                              // Texture verte XOR
//             texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);            // Texture de briques rouges
//             texture[6][TEX_WIDTH * y + x] = 65536 * ycolor;                              // Dégradé rouge
//             texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;               // Texture grise unie
//         }
//     }
// }

// Raycaster::~Raycaster() {
//     // Aucune action spécifique requise ici pour le moment
// }

// void Raycaster::cast_rays(Camera& cam, int worldMap[][MAP_WIDTH]) {
//     // Parcourir chaque colonne verticale de l'écran
//     for (int x = 0; x < SCREEN_WIDTH; x++) {
//         // Calcul de la direction du rayon en x
//         double cameraX = 2.0 * x / SCREEN_WIDTH - 1.0; // [-1, 1]
//         Vector2D<double> rayDir(
//             cam.direction.getX() + cam.plane.getX() * cameraX,
//             cam.direction.getY() + cam.plane.getY() * cameraX
//         );

//         ////////// ALGORITHME DDA //////////
//         // La cellule où se trouve le rayon à cet instant
//         Vector2D<int> map(
//             cam.position.getX(),
//             cam.position.getY()
//         );

//         // Longueur du rayon suivant les directions x et y
//         Vector2D<double> sideDist;

//         // Longueur du rayon de la position actuelle à la prochaine intersection
//         Vector2D<double> deltaDist(
//             (rayDir.getX() == 0) ? 1e30 : std::abs(1 / rayDir.getX()),
//             (rayDir.getY() == 0) ? 1e30 : std::abs(1 / rayDir.getY())
//         );

//         // Distance perpendiculaire au mur
//         double perpWallDist;

//         // Direction du pas suivant en x ou y (+1 ou -1)
//         Vector2D<int> step;

//         // Calcul des valeurs initiales
//         if (rayDir.getX() < 0) {
//             step.setX(-1);
//             sideDist.setX((cam.position.getX() - map.getX()) * deltaDist.getX());
//         } else {
//             step.setX(1);
//             sideDist.setX((map.getX() + 1.0 - cam.position.getX()) * deltaDist.getX());
//         }
//         if (rayDir.getY() < 0) {
//             step.setY(-1);
//             sideDist.setY((cam.position.getY() - map.getY()) * deltaDist.getY());
//         } else {
//             step.setY(1);
//             sideDist.setY((map.getY() + 1.0 - cam.position.getY()) * deltaDist.getY());
//         }

//         // Application de l'algorithme DDA
//         int hit = 0;
//         bool wasHorizontal; // Type de collision (horizontale ou verticale)
//         while (hit == 0) {
//             // Saut vers la prochaine cellule
//             if (sideDist.getX() < sideDist.getY()) {
//                 sideDist.setX(sideDist.getX() + deltaDist.getX());
//                 map.setX(map.getX() + step.getX());
//                 wasHorizontal = true; // Collision horizontale
//             } else {
//                 sideDist.setY(sideDist.getY() + deltaDist.getY());
//                 map.setY(map.getY() + step.getY());
//                 wasHorizontal = false; // Collision verticale
//             }

//             // Vérifier si le rayon a touché un mur
//             if (worldMap[map.getX()][map.getY()] > 0) hit = 1;
//         }

//         // Calcul de la distance perpendiculaire au mur
//         if (wasHorizontal) perpWallDist = (sideDist.getX() - deltaDist.getX());
//         else perpWallDist = (sideDist.getY() - deltaDist.getY());

//         // Numéro de la texture à utiliser
//         int texNum = worldMap[map.getX()][map.getY()] - 1;

//         // wallX correspond à l'endroit exact où le mur a été touché
//         double wallX;
//         if (wasHorizontal) wallX = cam.position.getY() + perpWallDist * rayDir.getY();
//         else               wallX = cam.position.getX() + perpWallDist * rayDir.getX();
//         wallX -= floor(wallX);

//         // Coordonnée X de la texture
//         int texX = int(wallX * (double)TEX_WIDTH);
//         if ((wasHorizontal && rayDir.getX() > 0) || (!wasHorizontal && rayDir.getY() < 0)) {
//             texX = TEX_WIDTH - texX - 1;
//         }

//         // Calcul de la hauteur de la ligne
//         int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

//         // Déterminer le début et la fin de la ligne à dessiner
//         int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
//         if (drawStart < 0) drawStart = 0;
//         int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
//         if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

//         // Remplissage de la bande verticale
//         double stripe_step = (double)TEX_HEIGHT / lineHeight;
//         double texPos = (double)(drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * stripe_step;
//         for (int y = drawStart; y < drawEnd; y++) {
//             int texY = (int)texPos & (TEX_HEIGHT - 1);
//             texPos += stripe_step;
//             Uint32 color = texture[texNum][TEX_HEIGHT * texY + texX];
//             if (!wasHorizontal) color = (color >> 1) & 8355711; // Assombrir pour les ombres
//             // buffer[y][x] = color;
//             }

//     }
// }

// void Raycaster::render(SDL_Renderer* renderer, SDL_Texture* bufferTex) {
//     // Mettre à jour la texture avec le buffer
//     SDL_UpdateTexture(bufferTex, nullptr, buffer, SCREEN_WIDTH * sizeof(Uint32));
//     SDL_RenderCopy(renderer, bufferTex, nullptr, nullptr);

//     // Réinitialiser le buffer
//     for (int y = 0; y < SCREEN_HEIGHT; y++) {
//         for (int x = 0; x < SCREEN_WIDTH; x++) {
//             buffer[y][x] = 0;
//         }
//     }
// }
