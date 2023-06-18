#include <filesystem>

#include "headers/utils.hpp"

using namespace std;

namespace fs = std::filesystem;

void utils::toggle(bool &boolean)
{
	boolean = !boolean;
}

void utils::createFolder(std::string path)
{
	if (fs::is_regular_file(path))
	{
		fs::remove(path);
	}
	if (!fs::is_directory(path))
	{
		fs::create_directory(path);
	}
}

std::string utils::replaceStringSubstring(std::string string, std::string substring, std::string replacement)
{
	string.replace(string.find(substring), substring.size(), replacement);
	return string;
}

float utils::degToRad(float deg)
{
	return deg * (PI / 180);
}

float utils::radToDeg(float rad)
{
	return rad * (180 / PI);
}

void utils::printMatrix(Matrix A)
{
	int rows = A   .size();
	int cols = A[0].size();

	cout << "Matrix:" << "\n";
	cout << "[" << "\n";
	for (int row = 0; row < rows; row++)
	{
		cout << "  " << "[";
		for (int col = 0; col < cols; col++)
		{
			cout << A[row][col];
			if (col < cols - 1)
			{
				cout << " ";
			}
		}
		cout << "]" << "\n";
	}
	cout << "]" << "\n";
}

Matrix utils::multiplyMatrices(Matrix A, Matrix B)
{
	int A_rows = A   .size();
	int A_cols = A[0].size();
	int B_rows = B   .size();
	int B_cols = B[0].size();

	if (A_cols != B_rows)
	{
		cout << "Invalid matrices." << "\n";
		return {{0}};
	}

	Matrix C;

	for (int row = 0; row < A_rows; row++)
	{
		C.push_back({});
		for (int col = 0; col < B_cols; col++)
		{
			float value = 0;

			for (int i = 0; i < A_cols; i++)
			{
				value += A[row][i] * B[i][col];
			}

			C[row].push_back(value);
		}
	}

	return C;
}

Matrix utils::x_3d_rotation_matrix(float a)
{
	return {
		{       1,       0,       0},
		{       0, +cos(a), -sin(a)},
		{       0, +sin(a), +cos(a)}
	};
}

Matrix utils::y_3d_rotation_matrix(float a)
{
	return {
		{ +cos(a),       0, +sin(a)},
		{       0,       1,       0},
		{ -sin(a),       0, +cos(a)}
	};
}

Matrix utils::z_3d_rotation_matrix(float a)
{
	return {
		{ +cos(a), -sin(a),       0},
		{ +sin(a), +cos(a),       0},
		{       0,       0,       1}
	};
}

Matrix utils::Vector3f_to_Matrix(Vector3f vector)
{
	return {
		{vector.x},
		{vector.y},
		{vector.z}
	};
}

Matrix utils::Vector2f_to_Matrix(Vector2f vector)
{
	return {
		{vector.x},
		{vector.y}
	};
}

Vector2f utils::rotate_2d_position(Vector2f position, Vector2f origo, float deg)
{
	float rad = degToRad(deg);
	Matrix rotated = multiplyMatrices(
		{
			{cos(rad), -sin(rad)},
			{sin(rad),  cos(rad)}
		},
		Vector2f_to_Matrix(position - origo)
	);

	return {
		rotated[0][0] + origo.x,
		rotated[1][0] + origo.y
	};
}
