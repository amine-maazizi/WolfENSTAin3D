/**
 * @file        billboard.hpp
 * @brief       fichier entête qui definit les billboard 
 * @author      Amine Maazizi
 * @date        2024-12-27
 * @version     1.0
 * 
 * @details
 * - Les billboard sont les sprite 2D qui reste face à la camera dans un raycasteur.
 *  
 * @note
 * Tous les attribues sont publiques pour le moment 
 */

#pragma once

#include <engine/vector2D.hpp>


class Billboard {
    public:
        Billboard(Vector2D<double>, int);
        Billboard(double, double, int);

        Vector2D<double> position;
        int texID;
};