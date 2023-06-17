#pragma once

template <typename T>
struct Vector3
{
	T x = 0;
	T y = 0;
	T z = 0;

	Vector3() {}

	Vector3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

template <typename T>
Vector3<T> operator - (const Vector3<T> right)
{
	return Vector3<T>(-right.x, -right.y, -right.z);
}

template <typename T>
Vector3<T> operator - (const Vector3<T> left, const Vector3<T> right)
{
	return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
}

template <typename T>
Vector3<T> operator -= (Vector3<T> &left, const Vector3<T> right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}

template <typename T>
Vector3<T> operator + (const Vector3<T> right)
{
	return Vector3<T>(right.x, right.y, right.z);
}

template <typename T>
Vector3<T> operator + (const Vector3<T> left, const Vector3<T> right)
{
	return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
}

template <typename T>
Vector3<T> operator += (Vector3<T> &left, const Vector3<T> right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}

template <typename T>
Vector3<T> operator * (const Vector3<T> left, const T right)
{
	return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

template <typename T>
Vector3<T> operator * (const T left, const Vector3<T> right)
{
	return Vector3<T>(left * right.x, left * right.y, left * right.z);
}

template <typename T>
Vector3<T> operator *= (Vector3<T> &left, const T right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}

template <typename T>
Vector3<T> operator / (const Vector3<T> left, const T right)
{
	return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

template <typename T>
Vector3<T> operator /= (Vector3<T> &left, const T right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}

template <typename T>
bool operator == (const Vector3<T> left, const Vector3<T> right)
{
	return left.x == right.x
	       &&
	       left.y == right.y
	       &&
	       left.z == right.z;
}

template <typename T>
bool operator != (const Vector3<T> left, const Vector3<T> right)
{
	return !(left == right);
}

typedef Vector3<int>          Vector3i;
typedef Vector3<unsigned int> Vector3u;
typedef Vector3<float>        Vector3f;
typedef Vector3<double>       Vector3d;
