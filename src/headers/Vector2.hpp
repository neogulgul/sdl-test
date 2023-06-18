#pragma once

template <typename T>
struct Vector2
{
	T x = 0;
	T y = 0;

	Vector2() {}

	Vector2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
};

template <typename T>
Vector2<T> operator - (const Vector2<T> right)
{
	return Vector2<T>(-right.x, -right.y);
}

template <typename T>
Vector2<T> operator - (const Vector2<T> left, const Vector2<T> right)
{
	return Vector2<T>(left.x - right.x, left.y - right.y);
}

template <typename T>
Vector2<T> operator -= (Vector2<T> &left, const Vector2<T> right)
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template <typename T>
Vector2<T> operator + (const Vector2<T> right)
{
	return Vector2<T>(right.x, right.y);
}

template <typename T>
Vector2<T> operator + (const Vector2<T> left, const Vector2<T> right)
{
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
Vector2<T> operator += (Vector2<T> &left, const Vector2<T> right)
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

template <typename T>
Vector2<T> operator * (const Vector2<T> left, const T right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
Vector2<T> operator * (const T left, const Vector2<T> right)
{
	return Vector2<T>(left * right.x, left * right.y);
}

template <typename T>
Vector2<T> operator * (const Vector2<T> left, const Vector2<T> right)
{
	return Vector2<T>(left.x * right.x, left.y * right.y);
}

template <typename T>
Vector2<T> operator *= (Vector2<T> &left, const T right)
{
	left.x *= right;
	left.y *= right;
	return left;
}

template <typename T>
Vector2<T> operator *= (Vector2<T> &left, const Vector2<T> right)
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

template <typename T>
Vector2<T> operator / (const Vector2<T> left, const T right)
{
	return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
Vector2<T> operator / (const Vector2<T> left, const Vector2<T> right)
{
	return Vector2<T>(left.x / right.x, left.y / right.y);
}

template <typename T>
Vector2<T> operator /= (Vector2<T> &left, const T right)
{
	left.x /= right;
	left.y /= right;
	return left;
}

template <typename T>
bool operator == (const Vector2<T> left, const Vector2<T> right)
{
	return left.x == right.x
	       &&
	       left.y == right.y;
}

template <typename T>
bool operator != (const Vector2<T> left, const Vector2<T> right)
{
	return !(left == right);
}

typedef Vector2<int>          Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float>        Vector2f;
typedef Vector2<double>       Vector2d;
