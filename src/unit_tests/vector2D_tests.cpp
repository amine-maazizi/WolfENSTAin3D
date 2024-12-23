/**
 * @file        vector2D_tests.cpp
 * @brief       tests unitaires pour la class Vector2D
 * @author      Amine Maazizi
 * @date        2024-12-23
 * @version     1.0
 * 
 * @details
 * 
 * @note
 */

#include <gtest/gtest.h>
#include "engine/vector2D.hpp"

// Tester le constructor
TEST(Vector2DTests, DefaultConstructor) {
    Vector2D<int> vec;
    EXPECT_EQ(vec.getX(), 0);
    EXPECT_EQ(vec.getY(), 0);
    EXPECT_DOUBLE_EQ(vec.getLength(), 0.0);
}

// Tester le constructor parametrizer
TEST(Vector2DTests, ParameterizedConstructor) {
    Vector2D<double> vec(3.0, 4.0);
    EXPECT_DOUBLE_EQ(vec.getX(), 3.0);
    EXPECT_DOUBLE_EQ(vec.getY(), 4.0);
    EXPECT_DOUBLE_EQ(vec.getLength(), 5.0);
}

// Tester le vecteur null
TEST(Vector2DTests, ZeroVector) {
    auto vec = Vector2D<double>::zeroVector();
    EXPECT_DOUBLE_EQ(vec.getX(), 0.0);
    EXPECT_DOUBLE_EQ(vec.getY(), 0.0);
    EXPECT_DOUBLE_EQ(vec.getLength(), 0.0);
}

// Tester la normalisation
TEST(Vector2DTests, Normalize) {
    Vector2D<double> vec(3.0, 4.0);
    vec.normalize();
    EXPECT_DOUBLE_EQ(vec.getX(), 3.0 / 5.0);
    EXPECT_DOUBLE_EQ(vec.getY(), 4.0 / 5.0);
    EXPECT_DOUBLE_EQ(vec.getLength(), 1.0);
}

// Tester le calcul de la normal
TEST(Vector2DTests, ComputeNormal) {
    Vector2D<double> vec(1.0, 0.0);
    auto normal = vec.computeNormal();
    EXPECT_DOUBLE_EQ(normal.getX(), 0.0);
    EXPECT_DOUBLE_EQ(normal.getY(), 1.0);
}

// Tester l'addition
TEST(Vector2DTests, AdditionOperator) {
    Vector2D<double> vec1(1.0, 2.0);
    Vector2D<double> vec2(3.0, 4.0);
    auto result = vec1 + vec2;
    EXPECT_DOUBLE_EQ(result.getX(), 4.0);
    EXPECT_DOUBLE_EQ(result.getY(), 6.0);
}

// Soustraction
TEST(Vector2DTests, SubtractionOperator) {
    Vector2D<double> vec1(5.0, 7.0);
    Vector2D<double> vec2(2.0, 3.0);
    auto result = vec1 - vec2;
    EXPECT_DOUBLE_EQ(result.getX(), 3.0);
    EXPECT_DOUBLE_EQ(result.getY(), 4.0);
}

// Multiplication scalaire
TEST(Vector2DTests, ScalarMultiplicationOperator) {
    Vector2D<double> vec(2.0, 3.0);
    auto result = vec * 2.0;
    EXPECT_DOUBLE_EQ(result.getX(), 4.0);
    EXPECT_DOUBLE_EQ(result.getY(), 6.0);
}

// Produit scalaire
TEST(Vector2DTests, DotProductOperator) {
    Vector2D<double> vec1(1.0, 2.0);
    Vector2D<double> vec2(3.0, 4.0);
    double dotProduct = vec1 * vec2;
    EXPECT_DOUBLE_EQ(dotProduct, 11.0);
}

// Affichage
TEST(Vector2DTests, OutputStreamOperator) {
    Vector2D<double> vec(1.5, 2.5);
    std::ostringstream os;
    os << vec;
    EXPECT_EQ(os.str(), "(x: 1.5, y: 2.5)");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}