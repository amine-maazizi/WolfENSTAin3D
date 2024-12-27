/**
 * @file        Vector2D.hpp
 * @brief       Class représentant un vecteur deux dimensionnel.
 * @author      Amine Maazizi
 * @date        2024-12-23
 * @version     1.0
 * 
 * @details
 * Ce fichier déclare les classes et fonctions principales pour une représentation d'un vecteur en 2D, 
 * notamment sa longeur et des opérations surchagées.
 * 
 * @note
 * Usage de patrons de class pour pouvoir gérer les vecteur entiers et flottant.
 */


#pragma once

#include <cmath>
#include <iostream>
#include <type_traits>


template <typename T>
class Vector2D {
private:
    T x;
    T y;
    double length;

public:
    // Constructors
    Vector2D() : x(0), y(0), length(0.0) {}
    Vector2D(T x, T y) : x(x), y(y), length(sqrt(x*x + y*y)) {}

    template <typename U>
    Vector2D(const Vector2D<U>& other) : x(static_cast<T>(other.getX())), y(static_cast<T>(other.getY())) {}

    // Accessors
    T getX() const { return x; }
    T getY() const { return y; }
    double getLength() const { return length; }

    void setX(T xVal) { x = xVal; length = sqrt(x*x + y*y);}
    void setY(T yVal) { y = yVal; length = sqrt(x*x + y*y);}

    // Casting Functions
    template <typename U>
    explicit operator Vector2D<U>() const {
        return Vector2D<U>(static_cast<U>(x), static_cast<U>(y));
    }

    // Overloaded Operators
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D operator*(T scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D operator/(T scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    template <typename U>
    Vector2D operator+(const Vector2D<U>& other) const {
        return Vector2D(x + static_cast<T>(other.getX()), y + static_cast<T>(other.getY()));
    }

    template <typename U>
    Vector2D operator-(const Vector2D<U>& other) const {
        return Vector2D(x - static_cast<T>(other.getX()), y - static_cast<T>(other.getY()));
    }

    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2D& operator*=(T scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2D& operator/=(T scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Utility Functions
    double length() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D normalized() const {
        double len = length();
        return Vector2D(x / len, y / len);
    }

    // Overloaded Output Operator
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};
