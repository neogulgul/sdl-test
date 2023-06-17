#pragma once

#include <string>

int charToHexInt(char c);

struct Color
{
	int r = -1;
	int g = -1;
	int b = -1;
	int a = -1;

	Color(int r, int g, int b, int a = 255);

	Color(std::string hexString);

	static const Color Black;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Magenta;
	static const Color Cyan;
	static const Color Transparent;
};
