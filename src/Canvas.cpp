#include "Canvas.h"

Canvas::Canvas(int width, int height) {
	this->width = width;
	this->height = height;

	for (int i = 0; i < height; ++i) {
		this->pixels.push_back(vector<Color>());
		for (int j = 0; j < width; ++j) {
			this->pixels[i].push_back(Color(0, 0, 0));
		}
	}
}

void Canvas::writePixel(int x, int y, Color c) {
	this->pixels[y][x] = c;
}

Color Canvas::pixelAt(int x, int y) {
	return this->pixels[y][x];
}