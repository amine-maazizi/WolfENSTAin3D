#include <engine/billboard.hpp>

Billboard::Billboard(Vector2D<double> pos, int id) : position(pos), texID(id), visible(true) {
}

Billboard::Billboard(double x, double y, int id) : position(Vector2D<double>(x, y)), texID(id), visible(true) {
}