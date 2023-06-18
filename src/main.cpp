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

	Mesh() {}

	Mesh(std::vector<Triangle> faces)
	{
		this->faces = faces;
	}
};

struct Cuboid
{
	Vector3f position;
	Vector3f size;
	Mesh mesh;

	Color color_1 = Color(255, 0, 0, 63);
	Color color_2 = Color(0, 255, 0, 63);
	Color color_3 = Color(0, 0, 255, 63);

	Cuboid(Vector3f position, Vector3f size)
	{
		this->position = position;
		this->size = size;

		Vector3f min = {
			position.x - size.x / 2,
			position.y - size.y / 2,
			position.z - size.z / 2
		};

		Vector3f max = {
			position.x + size.x / 2,
			position.y + size.y / 2,
			position.z + size.z / 2
		};

		this->mesh = Mesh({
			// NORTH
			{ Vector3f(min.x, min.y, min.z), Vector3f(min.x, max.y, min.z), Vector3f(max.x, max.y, min.z) },
			{ Vector3f(min.x, min.y, min.z), Vector3f(max.x, max.y, min.z), Vector3f(max.x, min.y, min.z) },
			// SOUTH
			{ Vector3f(max.x, min.y, max.z), Vector3f(max.x, max.y, max.z), Vector3f(min.x, max.y, max.z) },
			{ Vector3f(max.x, min.y, max.z), Vector3f(min.x, max.y, max.z), Vector3f(min.x, min.y, max.z) },
			// WEST
			{ Vector3f(max.x, min.y, min.z), Vector3f(max.x, max.y, min.z), Vector3f(max.x, max.y, max.z) },
			{ Vector3f(max.x, min.y, min.z), Vector3f(max.x, max.y, max.z), Vector3f(max.x, min.y, max.z) },
			// EAST
			{ Vector3f(min.x, min.y, max.z), Vector3f(min.x, max.y, max.z), Vector3f(min.x, max.y, min.z) },
			{ Vector3f(min.x, min.y, max.z), Vector3f(min.x, max.y, min.z), Vector3f(min.x, min.y, min.z) },
			// TOP
			{ Vector3f(min.x, max.y, min.z), Vector3f(min.x, max.y, max.z), Vector3f(max.x, max.y, max.z) },
			{ Vector3f(min.x, max.y, min.z), Vector3f(max.x, max.y, max.z), Vector3f(max.x, max.y, min.z) },
			// BOTTOM
			{ Vector3f(max.x, min.y, max.z), Vector3f(min.x, min.y, max.z), Vector3f(min.x, min.y, min.z) },
			{ Vector3f(max.x, min.y, max.z), Vector3f(min.x, min.y, min.z), Vector3f(max.x, min.y, min.z) }
		});
	}

	void setColors(Color color_1, Color color_2, Color color_3)
	{
		this->color_1 = color_1;
		this->color_2 = color_2;
		this->color_3 = color_3;
	}
};

Vector2f project_3d_to_2d(Vector3f position, View view)
{
	float fovRad = utils::degToRad(fov);
	return {
		position.x / (position.z * std::tan(fovRad / 2)),
		position.y / (position.z * std::tan(fovRad / 2))
	};
}

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initalize SDL2." << "\n" << SDL_GetError() << "\n";
		return -1;
	}

	View view({50, 50}, {100, 100});
	RenderWindow window("Hello, World!", {1024, 1024}, &view);

	float viewRotationStep = 0.5;

	float cubeRotation = 0;
	float cubeRotationStep = 1;

	bool paused = false;

	std::vector<Cuboid> cuboids = {
		Cuboid({-0.5, -0.5, 1}, {0.25, 0.25, 0.25}),
		Cuboid({ 0.0, -0.5, 1}, {0.25, 0.25, 0.25}),
		Cuboid({ 0.5, -0.5, 1}, {0.25, 0.25, 0.25}),

		Cuboid({-0.5,  0.0, 1}, {0.25, 0.25, 0.25}),
		Cuboid({ 0.0,  0.0, 1}, {0.25, 0.25, 0.25}),
		Cuboid({ 0.5,  0.0, 1}, {0.25, 0.25, 0.25}),

		Cuboid({-0.5,  0.5, 1}, {0.25, 0.25, 0.25}),
		Cuboid({ 0.0,  0.5, 1}, {0.25, 0.25, 0.25}),
		Cuboid({ 0.5,  0.5, 1}, {0.25, 0.25, 0.25})
	};

	for (int i = 0; i < cuboids.size(); i++)
	{
		if (i % 2 != 0)
		{
			Cuboid* cuboid = &cuboids[i];
			// cuboid->size / 2.f;
			cuboid->setColors(
				Color(255, 255, 0, 63),
				Color(255, 0, 255, 63),
				Color(0, 255, 255, 63)
			);
		}
	}

	while (window.is_open)
	{
		SDL_Delay(1000 / fps);

		bool takeScreenshot = false;

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					window.close();
					break;

				case SDL_KEYUP:
					{
						SDL_Keycode key = event.key.keysym.sym;
						switch (key)
						{
							case SDLK_1: view.rotation =   0; cubeRotation =   0; break;
							case SDLK_2: view.rotation =  90; cubeRotation =  90; break;
							case SDLK_3: view.rotation = 180; cubeRotation = 180; break;
							case SDLK_4: view.rotation = 270; cubeRotation = 270; break;
							case SDLK_SPACE: utils::toggle(paused); break;
							case SDLK_F12: takeScreenshot = true; break;
						}
					}
					break;
			}
		}

		if (!paused)
		{
			view.rotation += viewRotationStep; if (view.rotation > 360) { view.rotation -= 360; }

			cubeRotation += cubeRotationStep; if (cubeRotation > 360) { cubeRotation -= 360; }

			// std::cout << view.rotation << "\n";
			// std::cout << cubeRotation << "\n";
		}

		window.clear(colors::background);

		// // top to bottom crosshair
		// window.drawLine(
		// 	window.getViewCenter() - Vector2f(0.f, view.size.y / 2.f),
		// 	window.getViewCenter() + Vector2f(0.f, view.size.y / 2.f),
		// 	colors::crosshair
		// );
		// // left to right crosshair
		// window.drawLine(
		// 	window.getViewCenter() - Vector2f(view.size.x / 2.f, 0.f),
		// 	window.getViewCenter() + Vector2f(view.size.x / 2.f, 0.f),
		// 	colors::crosshair
		// );

		for (Cuboid cuboid : cuboids)
		{
			for (int i = 0; i < cuboid.mesh.faces.size(); i++)
			{
				Triangle tri = cuboid.mesh.faces[i];

				std::vector<Vector3f> vertices(std::begin(tri.vertices), std::end(tri.vertices));

				std::vector<Vector2f> vertices_2d;

				for (Vector3f vertex : vertices)
				{
					Matrix rotated;
					rotated = utils::multiplyMatrices(
						utils::x_3d_rotation_matrix(utils::degToRad(cubeRotation)),
						utils::Vector3f_to_Matrix(vertex - cuboid.position)
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

					vertex += cuboid.position;

					Vector2f vertex_2d = project_3d_to_2d(vertex, view);
					vertex_2d *= view.size / 2.f;
					vertices_2d.push_back(vertex_2d);
				}

				std::vector<Color> colors;
				if (i % 2 == 0)
				{
					colors = {
						cuboid.color_1,
						cuboid.color_2,
						cuboid.color_3
					};
				}
				else
				{
					colors = {
						cuboid.color_1,
						cuboid.color_3,
						cuboid.color_2
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
		}

		window.display();

		if (takeScreenshot) { window.screenshot(); }
	}

	return 0;
}
