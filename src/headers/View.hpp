#pragma once

#include "Vector2.hpp"

struct View
{
	Vector2f position;
	Vector2f size;
	float rotation = 0;

	View() {}

	View(Vector2f position, Vector2f size)
	{
		this->position = position;
		this->size = size;
	}
};
