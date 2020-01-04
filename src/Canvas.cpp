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
		string tempPPM = "";
		for (int j = 0; j < c->width; ++j) {
			Color pixel = c->pixelAt(j, i);
			float r, g, b;

			r = pixel.red <= 0 ? 0 : pixel.red;
			r = pixel.red >= 1.0 ? 255 : r * 256;
			g = pixel.green <= 0 ? 0 : pixel.green;
			g = pixel.green >= 1.0 ? 255 : g * 256;
			b = pixel.blue <= 0 ? 0 : pixel.blue;
			b = pixel.blue >= 1.0 ? 255 : b * 256;

			if (tempPPM.length() == 0) {
				tempPPM += to_string(int(r)) + " " + to_string(int(g)) + " " + to_string(int(b));
			}
			else {
				tempPPM += " " + to_string(int(r)) + " " + to_string(int(g)) + " " + to_string(int(b));
			}
		}
		ppmString.push_back(tempPPM);
	}

	return ppmString;
}