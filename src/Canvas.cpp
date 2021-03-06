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

string* convertColorValues(Color* pixel) {
	float r, g, b;

	r = pixel->red <= 0 ? 0 : pixel->red;
	r = pixel->red >= 1.0 ? 255 : r * 256;
	g = pixel->green <= 0 ? 0 : pixel->green;
	g = pixel->green >= 1.0 ? 255 : g * 256;
	b = pixel->blue <= 0 ? 0 : pixel->blue;
	b = pixel->blue >= 1.0 ? 255 : b * 256;

	string* pixels = new string[3]{ to_string(int(r)), to_string(int(g)), to_string(int(b)) };
	return pixels;
}

vector<string> canvasToPPM(Canvas* c) {
	vector<string> ppmString;
	ppmString.push_back("P3");
	ppmString.push_back(to_string(c->width) + " " + to_string(c->height));
	ppmString.push_back("255");

	float count = 0;
	float progress = 0;
	float total = c->width * c->height;
	for (int i = 0; i < c->height; ++i) {
		string tempPPM = "";
		for (int j = 0; j < c->width; ++j) {
			Color* pixel = &c->pixelAt(j, i);
			string* pixels = convertColorValues(pixel);

			for (int k = 0; k < 3; ++k) {
				if (tempPPM.length() + pixels[k].length() + 1 > 70) {
					ppmString.push_back(tempPPM);
					tempPPM = pixels[k];
				}
				else {
					tempPPM += tempPPM.length() == 0 ? pixels[k] : " " + pixels[k];
				}
			}
			delete[]pixels;

			++count;
			progress = count / total;
			std::cout << progress << std::endl;
		}
		ppmString.push_back(tempPPM);
	}
	ppmString[ppmString.size() - 1] += "\n";

	return ppmString;
}