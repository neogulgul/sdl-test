#include "headers/RenderWindow.hpp"
#include "headers/utils.hpp"

RenderWindow::RenderWindow(const char* title, Vector2f windowSize, View* view)
{
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowSize.x,
		windowSize.y,
		0
	);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowResizable(window, SDL_TRUE);

	this->view = view;
}

void RenderWindow::close()
{
	is_open = false;
}

void RenderWindow::setRenderColor(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void RenderWindow::clear(Color color)
{
	setRenderColor(color);
	SDL_RenderClear(renderer);
}

void RenderWindow::drawPoint(Vector2f point, Color color)
{
	point = toViewCoord(point);
	setRenderColor(color);
	SDL_RenderDrawPointF(renderer, point.x, point.y);
}

void RenderWindow::drawLine(Vector2f start, Vector2f stop, Color color)
{
	start = toViewCoord(start);
	stop  = toViewCoord(stop);
	setRenderColor(color);
	SDL_RenderDrawLineF(renderer, start.x, start.y, stop.x, stop.y);
}

void RenderWindow::drawLines(std::vector<Vector2f> points, Color color)
{
	setRenderColor(color);

	std::vector<SDL_FPoint> vertices;

	for (int i = 0; i <= points.size(); i++)
	{
		int index;
		i == points.size() ? index = 0 : index = i;
		Vector2f point = toViewCoord(points[index]);
		vertices.push_back({point.x, point.y});
	}

	SDL_RenderDrawLinesF(renderer, vertices.data(), vertices.size());
}

void RenderWindow::drawGeometry(std::vector<Vector2f> points, std::vector<Color> colors)
{
	int sizeDifference = points.size() - colors.size();
	if (sizeDifference > 0)
	{
		for (int i = 0; i < sizeDifference; i++)
		{
			colors.push_back(Color::White);
		}
	}

	std::vector<SDL_Vertex> vertices;

	for (int i = 0; i < points.size(); i++)
	{
		Vector2f point = toViewCoord(points[i]);
		Color color = colors[i];

		vertices.push_back(
			SDL_Vertex(
				SDL_FPoint{point.x, point.y},
				SDL_Color{(Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a},
				SDL_FPoint{0, 0}
			)
		);
	}

	SDL_RenderGeometry(renderer, NULL, vertices.data(), vertices.size(), NULL, 0);
}

void RenderWindow::drawRect(Rect* rect, Color topLeft, Color topRight, Color bottomLeft, Color bottomRight)
{
	Vector2f topLeftPosition     = utils::rotate_2d_position(rect->getTopLeft    (), rect->position, rect->rotation);
	Vector2f topRightPosition    = utils::rotate_2d_position(rect->getTopRight   (), rect->position, rect->rotation);
	Vector2f bottomLeftPosition  = utils::rotate_2d_position(rect->getBottomLeft (), rect->position, rect->rotation);
	Vector2f bottomRightPosition = utils::rotate_2d_position(rect->getBottomRight(), rect->position, rect->rotation);

	drawGeometry(
		{
			topLeftPosition,
			bottomLeftPosition,
			bottomRightPosition,

			bottomRightPosition,
			topRightPosition,
			topLeftPosition
		},
		{
			topLeft,
			bottomLeft,
			bottomRight,

			bottomRight,
			topRight,
			topLeft
		}
	);
}

void RenderWindow::drawRect(Rect* rect, Color color)
{
	drawRect(rect, color, color, color, color);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

Vector2u RenderWindow::getSize()
{
	int width, height;

	SDL_GetWindowSize(window, &width, &height);

	return {
		(unsigned)width,
		(unsigned)height
	};
}

Vector2f RenderWindow::getViewCenter()
{
	return view->size / 2.f - view->position;
}

Vector2f RenderWindow::toViewCoord(Vector2f position)
{
	Vector2f windowSize((float)getSize().x, (float)getSize().y);
	Vector2f windowViewRatio = windowSize / view->size;
	Vector2f rotatedPosition = utils::rotate_2d_position(position, getViewCenter(), view->rotation);

	return (rotatedPosition + view->position) * windowViewRatio;
}
