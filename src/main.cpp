#include <iostream>

#include "headers/colors.hpp"
#include "headers/RenderWindow.hpp"
#include "headers/utils.hpp"
#include "headers/Vector3.hpp"

const unsigned int fps = 60;

const float fov = 90;

struct Triangle
{
	Vector3f vertices[3];
};

struct Mesh
{
	std::vector<Triangle> faces;

	Mesh(std::vector<Triangle> faces)
	{
		this->faces = faces;
	}
};

Vector2f project_3d_to_2d(Vector3f position)
{
	float fovRad = utils::degToRad(fov);
	return {
		position.x / (position.z * std::tan(fovRad / 2)),
		position.y / (position.z * std::tan(fovRad / 2))
	};
}

Vector2f normalise_to_screen_space(Vector2f position, View view)
{
	return {
		(position.x + 1) * view.size.x / 2 - view.position.x,
		(position.y + 1) * view.size.y / 2 - view.position.y
	};
}

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initalize SDL2." << "\n" << SDL_GetError() << "\n";
		return -1;
	}

	View view({320, 320}, {640, 640});
	RenderWindow window("Hello, World!", {640, 640}, &view);

	Rect rect({window.getViewCenter()}, {100, 100});
	rect.origin = {0.5, 0.5};

	bool up    = false;
	bool down  = false;
	bool left  = false;
	bool right = false;

	float min = -0.5;
	float max =  0.5;
	float cubeDepth = 2;
	float cubeRotation = 0;
	float cubeRotationStep = 1;
	Mesh cubeMesh({
		// NORTH
		{ Vector3f(min, min, min), Vector3f(min, max, min), Vector3f(max, max, min) },
		{ Vector3f(min, min, min), Vector3f(max, max, min), Vector3f(max, min, min) },
		// SOUTH
		{ Vector3f(max, min, max), Vector3f(max, max, max), Vector3f(min, max, max) },
		{ Vector3f(max, min, max), Vector3f(min, max, max), Vector3f(min, min, max) },
		// WEST
		{ Vector3f(max, min, min), Vector3f(max, max, min), Vector3f(max, max, max) },
		{ Vector3f(max, min, min), Vector3f(max, max, max), Vector3f(max, min, max) },
		// EAST
		{ Vector3f(min, min, max), Vector3f(min, max, max), Vector3f(min, max, min) },
		{ Vector3f(min, min, max), Vector3f(min, max, min), Vector3f(min, min, min) },
		// TOP
		{ Vector3f(min, max, min), Vector3f(min, max, max), Vector3f(max, max, max) },
		{ Vector3f(min, max, min), Vector3f(max, max, max), Vector3f(max, max, min) },
		// BOTTOM
		{ Vector3f(max, min, max), Vector3f(min, min, max), Vector3f(min, min, min) },
		{ Vector3f(max, min, max), Vector3f(min, min, min), Vector3f(max, min, min) }
	});

	while (window.is_open)
	{
		SDL_Delay(1000 / fps);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					window.close();
					break;

				case SDL_KEYDOWN:
				{
					SDL_Keycode key = event.key.keysym.sym;
					switch (key)
					{
						case SDLK_w: up    = true; break;
						case SDLK_s: down  = true; break;
						case SDLK_a: left  = true; break;
						case SDLK_d: right = true; break;
					}
				}
				break;

				case SDL_KEYUP:
				{
					SDL_Keycode key = event.key.keysym.sym;
					switch (key)
					{
						case SDLK_w: up    = false; break;
						case SDLK_s: down  = false; break;
						case SDLK_a: left  = false; break;
						case SDLK_d: right = false; break;
					}
				}
				break;
			}
		}

		if (up   ) { rect.position.y -= 10; }
		if (down ) { rect.position.y += 10; }
		if (left ) { rect.position.x -= 10; }
		if (right) { rect.position.x += 10; }

		// rect.rotation--;
		// view.rotation++;
		// if (rect.rotation > 360) { rect.rotation -= 360; }
		// if (view.rotation > 360) { view.rotation -= 360; }

		cubeRotation += cubeRotationStep;
		if (cubeRotation > 360) { cubeRotation -= 360; }

		window.clear(colors::background);

		// top to bottom crosshair
		window.drawLine(
			window.getViewCenter() - Vector2f(0.f, view.size.y / 2.f),
			window.getViewCenter() + Vector2f(0.f, view.size.y / 2.f),
			colors::crosshair
		);
		// left to right crosshair
		window.drawLine(
			window.getViewCenter() - Vector2f(view.size.x / 2.f, 0.f),
			window.getViewCenter() + Vector2f(view.size.x / 2.f, 0.f),
			colors::crosshair
		);

		// window.drawLines(
		// 	{
		// 		window.getViewCenter() + Vector2f(0, -view.size.y * 0.25),
		// 		window.getViewCenter() + Vector2f(-view.size.x * 0.25, 0),
		// 		window.getViewCenter() + Vector2f(0,  view.size.y * 0.25),
		// 		window.getViewCenter() + Vector2f( view.size.x * 0.25, 0)
		// 	},
		// 	Color("#cba6f7aa")
		// );

		// window.drawPoint(window.getViewCenter() + Vector2f(0, -view.size.y * 0.25), Color::Red);
		// window.drawPoint(window.getViewCenter() + Vector2f(0,  view.size.y * 0.25), Color::Green);
		// window.drawPoint(window.getViewCenter() + Vector2f(-view.size.x * 0.25, 0), Color::Blue);
		// window.drawPoint(window.getViewCenter() + Vector2f( view.size.x * 0.25, 0), Color::Yellow);

		// window.drawRect(&rect, Color::Red, Color::Green, Color::Blue, Color::Yellow);

		// drawing cube
		// for (int i = 0; i < cubeMesh.faces.size(); i++)
		// {
		// 	Triangle tri = cubeMesh.faces[i];

		// 	std::vector<Vector3f> vertices(std::begin(tri.vertices), std::end(tri.vertices));

		// 	std::vector<Vector2f> vertices_2d;

		// 	for (Vector3f vertex : vertices)
		// 	{
		// 		Matrix rotated;
		// 		rotated = utils::multiplyMatrices(
		// 			utils::x_3d_rotation_matrix(utils::degToRad(cubeRotation)),
		// 			utils::Vector3f_to_Matrix(vertex)
		// 		);
		// 		rotated = utils::multiplyMatrices(
		// 			utils::y_3d_rotation_matrix(utils::degToRad(cubeRotation)),
		// 			rotated
		// 		);
		// 		rotated = utils::multiplyMatrices(
		// 			utils::z_3d_rotation_matrix(utils::degToRad(cubeRotation)),
		// 			rotated
		// 		);

		// 		vertex.x = rotated[0][0];
		// 		vertex.y = rotated[1][0];
		// 		vertex.z = rotated[2][0];

		// 		vertex.z += cubeDepth;

		// 		vertices_2d.push_back(normalise_to_screen_space(project_3d_to_2d(vertex), view));
		// 	}

		// 	window.drawGeometry(
		// 		{
		// 			vertices_2d[0],
		// 			vertices_2d[1],
		// 			vertices_2d[2]
		// 		},
		// 		{
		// 			Color(255, 0, 0, 63),
		// 			Color(0, 255, 0, 63),
		// 			Color(0, 0, 255, 63)
		// 		}
		// 	);
		// }

		for (int i = 0; i < cubeMesh.faces.size(); i++)
		{
			Triangle tri = cubeMesh.faces[i];

			std::vector<Vector3f> vertices(std::begin(tri.vertices), std::end(tri.vertices));

			std::vector<Vector2f> vertices_2d;

			for (Vector3f vertex : vertices)
			{
				Matrix rotated;
				rotated = utils::multiplyMatrices(
					utils::x_3d_rotation_matrix(utils::degToRad(cubeRotation)),
					utils::Vector3f_to_Matrix(vertex)
				);
				rotated = utils::multiplyMatrices(
					utils::y_3d_rotation_matrix(utils::degToRad(cubeRotation)),
					rotated
				);
				rotated = utils::multiplyMatrices(
					utils::z_3d_rotation_matrix(utils::degToRad(cubeRotation)),
					rotated
				);

				vertex.x = rotated[0][0];
				vertex.y = rotated[1][0];
				vertex.z = rotated[2][0];

				vertex.z += cubeDepth;

				vertices_2d.push_back(normalise_to_screen_space(project_3d_to_2d(vertex), view));
			}

			std::vector<Color> colors;
			if (i % 2 == 0)
			{
				colors = {
					Color(255, 0, 0, 63),
					Color(0, 255, 0, 63),
					Color(0, 0, 255, 63)
				};
			}
			else
			{
				colors = {
					Color(255, 0, 0, 63),
					Color(0, 0, 255, 63),
					Color(0, 255, 0, 63)
				};
			}

			window.drawGeometry(
				{
					vertices_2d[0],
					vertices_2d[1],
					vertices_2d[2]
				},
				colors
			);
		}

		window.display();
	}

	return 0;
}
