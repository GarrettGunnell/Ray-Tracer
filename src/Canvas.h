#pragma once
#include "Color.h"
#include <string>
#include <iostream>
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

vector<string> canvasToPPM(Canvas* c);
string* convertColorValues(Color* pixel);