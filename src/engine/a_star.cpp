#include <engine/a_star.hpp>

AStar::AStar(int map[MAP_HEIGHT][MAP_WIDTH]) {
    std::memcpy(this->map, map, sizeof(int) * MAP_HEIGHT * MAP_WIDTH);
}

int AStar::heuristic(const Vector2D<int>& a, const Vector2D<int>& b) {
    // Using Manhattan distance as heuristic
    return std::abs(a.getX() - b.getX()) + std::abs(a.getY() - b.getY());
}

bool AStar::isValidMove(const Vector2D<int>& position) {
    return position.getX() >= 0 && position.getX() < MAP_WIDTH &&
           position.getY() >= 0 && position.getY() < MAP_HEIGHT &&
           map[position.getY()][position.getX()] != 1; // Check if the cell is not a wall
}

std::vector<Vector2D<int>> AStar::getNeighbors(const Vector2D<int>& position) {
    std::vector<Vector2D<int>> neighbors;
    int x = position.getX();
    int y = position.getY();

    // Four possible directions: up, down, left, right
    neighbors.push_back(Vector2D<int>(x + 1, y));
    neighbors.push_back(Vector2D<int>(x - 1, y));
    neighbors.push_back(Vector2D<int>(x, y + 1));
    neighbors.push_back(Vector2D<int>(x, y - 1));

    return neighbors;
}

std::vector<Vector2D<int>> AStar::findPath(const Vector2D<int>& start, const Vector2D<int>& goal) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::unordered_set<int> closedSet;
    std::unordered_map<int, int> openSetHash;  // Tracks nodes in open set for faster lookup

    openSet.push(Node{start, 0, heuristic(start, goal)});
    openSetHash[start.getY() * MAP_WIDTH + start.getX()] = 0;  // Initialize open set with start node

    std::unordered_map<int, Vector2D<int>> cameFrom;

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        // If we reached the goal, reconstruct the path
        if (current.position.getX() == goal.getX() && current.position.getY() == goal.getY()) {
            std::vector<Vector2D<int>> path;
            Vector2D<int> currentPos = goal;
            while (!(currentPos.getX() == start.getX() && currentPos.getY() == start.getY())) {
                path.push_back(currentPos);
                currentPos = cameFrom[currentPos.getY() * MAP_WIDTH + currentPos.getX()];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet.insert(current.position.getY() * MAP_WIDTH + current.position.getX());

        // Process each neighbor
        for (const Vector2D<int>& neighbor : getNeighbors(current.position)) {
            if (isValidMove(neighbor) && closedSet.find(neighbor.getY() * MAP_WIDTH + neighbor.getX()) == closedSet.end()) {
                int tentativeGCost = current.gCost + 1;
                int neighborHash = neighbor.getY() * MAP_WIDTH + neighbor.getX();
                bool inOpenSet = openSetHash.find(neighborHash) != openSetHash.end();

                // If the neighbor is not in the open set or a shorter path is found
                if (!inOpenSet || tentativeGCost < openSetHash[neighborHash]) {
                    openSet.push(Node{neighbor, tentativeGCost, heuristic(neighbor, goal)});
                    openSetHash[neighborHash] = tentativeGCost; // Update gCost in the hash map
                    cameFrom[neighbor.getY() * MAP_WIDTH + neighbor.getX()] = current.position;
                }
            }
        }
    }

    return {};  // Return an empty path if no path found
}
