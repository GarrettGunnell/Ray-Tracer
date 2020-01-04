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

vector<string> canvasToPPM(Canvas* c) {
	vector<string> ppmString;
	ppmString.push_back("P3");
	ppmString.push_back(to_string(c->width) + " " + to_string(c->height));
	ppmString.push_back("255");

	for (int i = 0; i < c->height; ++i) {
		for (int j = 0; j < c->width; ++j) {
			int a;
		}
	}

	return ppmString;
}