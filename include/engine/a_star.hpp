
/**
 * @file        a_star.hpp
 * @brief       Class implémentant l'algorithme de pathfinding A*
 * @author      Amine Maazizi
 * @date        2024-12-23
 * @version     1.0
 * 
 * @details
 * Heuristique : distance de Manhathan
 * 
 * @note
 */


#pragma once
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cstring>

#include <engine/vector2D.hpp>
#include <engine/constantes.hpp>

struct Node {
    Vector2D<int> position;
    int gCost;  // coût à partir du début
    int hCost;  // Heuristique à partir du but
    int fCost() const { return gCost + hCost; } // coût totale

    bool operator>(const Node& other) const {
        return fCost() > other.fCost();
    }
};

class AStar {
public:
    AStar(int map[MAP_HEIGHT][MAP_WIDTH]);

    std::vector<Vector2D<int>> findPath(const Vector2D<int>& start, const Vector2D<int>& goal);

private:
    int heuristic(const Vector2D<int>& a, const Vector2D<int>& b);
    bool isValidMove(const Vector2D<int>& position);
    std::vector<Vector2D<int>> getNeighbors(const Vector2D<int>& position);

    int map[MAP_HEIGHT][MAP_WIDTH];
};
