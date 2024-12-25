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

// Class template declaration
template <typename T>
class Vector2D {
private:
    T x, y;
    double length;

    double computeLength();

public:
    Vector2D();
    Vector2D(T x, T y);

    T getX() const;
    T getY() const;
    double getLength() const;

    void setX(const T x);
    void setY(const T y);

    // Utility 
    static Vector2D<T> zeroVector();
    void normalize();
    Vector2D<T> computeNormal();

    // Operators
    Vector2D<T> operator+(const Vector2D<T>& obj);
    Vector2D<T> operator-(const Vector2D<T>& obj);
    Vector2D<T> operator*(const double& scalar);
    double operator*(const Vector2D<T>& obj); // Produit scalaire

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector2D<U>& obj);
};

// Implementations
template <typename T>
Vector2D<T>::Vector2D() : x(0), y(0), length(0) {}

template <typename T>
Vector2D<T>::Vector2D(T x, T y) : x(x), y(y) {
    this->length = this->computeLength();
}

template <typename T>
T Vector2D<T>::getX() const {
    return this->x;
}

template <typename T>
T Vector2D<T>::getY() const {
    return this->y;
}

template <typename T>
double Vector2D<T>::getLength() const {
    return this->length;
}

template <typename T>
void Vector2D<T>::setX(const T x) {
    this->x = x;
    this->length = computeLength();
}

template <typename T>
void Vector2D<T>::setY(const T y) {
    this->y = y;
    this->length = computeLength();
}

template <typename T>
Vector2D<T> Vector2D<T>::zeroVector() {
    return Vector2D<T>{0, 0};
}

template <typename T>
void Vector2D<T>::normalize() {
    if (this->length == 0.0)
        return;
    this->x /= this->length;
    this->y /= this->length;
    this->length = 1.0;
}

template <typename T>
Vector2D<T> Vector2D<T>::computeNormal() {
    return Vector2D<T>{-this->y, this->x};
}

template <typename T>
double Vector2D<T>::computeLength() {
    return std::sqrt(this->x * this->x + this->y * this->y);
}

template <typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& obj) {
    return Vector2D<T>{this->x + obj.x, this->y + obj.y};
}

template <typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& obj) {
    return Vector2D<T>{this->x - obj.x, this->y - obj.y};
}

template <typename T>
Vector2D<T> Vector2D<T>::operator*(const double& scalar) {
    return Vector2D<T>{scalar * this->x, scalar * this->y};
}

template <typename T>
double Vector2D<T>::operator*(const Vector2D<T>& obj) {
    return this->x * obj.x + this->y * obj.y;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& obj) {
    os << "(x: " << obj.x << ", y: " << obj.y << ")";
    return os;
}
