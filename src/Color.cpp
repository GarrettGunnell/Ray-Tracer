#include "Color.h"
#include "Tuple.h"

Color::Color(float r, float g, float b) {
	this->red = r;
	this->blue = b;
	this->green = g;
}


bool operator== (const Color& c1, const Color& c2) {
	return equal(c1.red, c2.red) && equal(c1.blue, c2.blue) && equal(c1.green, c2.green);
}

Color operator+ (const Color& c1, const Color& c2) {
	return Color(c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue);
}

Color operator- (const Color& c1, const Color& c2) {
	return Color(c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue);
}

Color operator* (const Color& c, const float scalar) {
	return Color(c.red * scalar, c.green * scalar, c.blue * scalar);
}

Color operator* (const Color& c1, const Color& c2) {
	return Color(c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue);
}
