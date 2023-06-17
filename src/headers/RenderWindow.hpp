#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "Color.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"
#include "View.hpp"

struct RenderWindow
{
	bool is_open = true;

	SDL_Window* window;
	SDL_Renderer* renderer;

	View* view;

	RenderWindow(const char* title, Vector2f windowSize, View* view);

	void close();

	void setRenderColor(Color color);

	void clear(Color color);

	void drawPoint(Vector2f point, Color color = Color::White);

	void drawLine(Vector2f start, Vector2f stop, Color color = Color::White);

	void drawLines(std::vector<Vector2f> points, Color color = Color::White);

	void drawGeometry(std::vector<Vector2f> points, std::vector<Color> colors = {});

	void drawRect(Rect* rect, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight);

	void drawRect(Rect* rect, Color color = Color::White);

	void display();

	Vector2u getSize();

	Vector2f getViewCenter();

	Vector2f toViewCoord(Vector2f position);
};
