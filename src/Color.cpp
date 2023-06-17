#include "headers/Color.hpp"

int charToHexInt(char c)
{
	int i = (int)c;

	// numbers
	if (i >= '0' && i <= '9') { i -= '0'; }
	// uppercase letters
	if (i >= 'A' && i <= 'Z') { i -= 'A'; i += 10; }
	// lowercase letters
	if (i >= 'a' && i <= 'z') { i -= 'a'; i += 10; }

	return i;
}

const Color Color::Black      ("#000000");
const Color Color::White      ("#ffffff");
const Color Color::Red        ("#ff0000");
const Color Color::Green      ("#00ff00");
const Color Color::Blue       ("#0000ff");
const Color Color::Yellow     ("#ffff00");
const Color Color::Magenta    ("#ff00ff");
const Color Color::Cyan       ("#00ffff");
const Color Color::Transparent("#00000000");

Color::Color(int r, int g, int b, int a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(std::string hexString)
{
	if (hexString[0] == '#')
	{
		// alpha not specified
		if (hexString.size() == 7)
		{
			r = charToHexInt(hexString[1]) * 16 + charToHexInt(hexString[2]);
			g = charToHexInt(hexString[3]) * 16 + charToHexInt(hexString[4]);
			b = charToHexInt(hexString[5]) * 16 + charToHexInt(hexString[6]);
			a = 255;
		}
		// alpha specified
		else if (hexString.size() == 9)
		{
			r = charToHexInt(hexString[1]) * 16 + charToHexInt(hexString[2]);
			g = charToHexInt(hexString[3]) * 16 + charToHexInt(hexString[4]);
			b = charToHexInt(hexString[5]) * 16 + charToHexInt(hexString[6]);
			a = charToHexInt(hexString[7]) * 16 + charToHexInt(hexString[8]);
		}
	}

	if (r < 0 || r > 255) { r = 0; }
	if (g < 0 || g > 255) { g = 0; }
	if (b < 0 || b > 255) { b = 0; }
	if (a < 0 || a > 255) { a = 0; }
}
