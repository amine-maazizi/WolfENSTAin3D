/**
 * @file        raycaster.hpp
 * @brief       fichier entête du moteur du raycasting 
 * @author      Amine Maazizi
 * @date        2024-12-24
 * @version     1.0
 * 
 * @details
 * cette classe se chargera de lancer l'algorithme de raycasting 
 * 
 * @note
 * 
 * 
 */

#include <camera.hpp>
#include <constantes.hpp>
#include <cmath>

class Raycaster {
    public:
        Raycaster() = delete;
        static void raycast(Camera&, int**);
};