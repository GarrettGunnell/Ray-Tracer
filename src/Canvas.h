#pragma once
#include "Color.h"
#include <vector>

using namespace std;

class Canvas {
public:
	int width;
	int height;
	vector<vector<Color>> pixels;

	Canvas(int width, int height);
	void writePixel(int x, int y, Color c);
	Color pixelAt(int x, int y);
};