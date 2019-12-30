#include "Canvas.h"

Canvas::Canvas(int width, int height) {
	this->width = width;
	this->height = height;

	for (int i = 0; i < width; ++i) {
		this->pixels.push_back(vector<Color>());
		for (int j = 0; j < height; ++j) {
			this->pixels[i].push_back(Color(0, 0, 0));
		}
	}
}