#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "Vector2.hpp"
#include "Vector3.hpp"

#define Matrix std::vector<std::vector<float>>

const float PI = std::numbers::pi;

namespace utils
{
	void toggle(bool &boolean);

	void createFolder(std::string path);

	std::string replaceStringSubstring(std::string string, std::string substring, std::string replacement = "");

	float degToRad(float deg);

	float radToDeg(float rad);

	void printMatrix(Matrix A);

	Matrix multiplyMatrices(Matrix A, Matrix B);

	Matrix x_3d_rotation_matrix(float a);

	Matrix y_3d_rotation_matrix(float a);

	Matrix z_3d_rotation_matrix(float a);

	Matrix Vector3f_to_Matrix(Vector3f vector);

	Matrix Vector2f_to_Matrix(Vector2f vector);

	Vector2f rotate_2d_position(Vector2f position, Vector2f origo, float deg);
}
