/**
 * @file        camera.hpp
 * @brief       fichier entête de la camera  
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 * 
 * @note
 * cette classe servira de classe de base pour l'entité joueur par la suite
 * 
 */

#include <vector2D.hpp>

class Camera {
    public:
        Vector2D<double> position;
        Vector2D<double> direction;
        Vector2D<double> plane;
};