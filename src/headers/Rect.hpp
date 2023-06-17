#pragma once

#include "Vector2.hpp"

struct Rect
{
	Vector2f position;
	Vector2f size;
	Vector2f origin;
	float rotation = 0;

	Rect() {}

	Rect(Vector2f position, Vector2f size)
	{
		this->position = position;
		this->size = size;
	}

	Vector2f getCenter()
	{
		return { position + size / 2.f - origin * size };
	}

	float getTop   () { return getCenter().y - size.y / 2; }
	float getBottom() { return getCenter().y + size.y / 2; }
	float getLeft  () { return getCenter().x - size.x / 2; }
	float getRight () { return getCenter().x + size.x / 2; }

	Vector2f getTopLeft()
	{
		return {
			getLeft(),
			getTop()
		};
	}

	Vector2f getTopRight()
	{
		return {
			getRight(),
			getTop()
		};
	}

	Vector2f getBottomLeft()
	{
		return {
			getLeft(),
			getBottom()
		};
	}

	Vector2f getBottomRight()
	{
		return {
			getRight(),
			getBottom()
		};
	}
};
