#include <iostream>
#include <fstream>
#include <math.h>
#include "Tuple.h"
#include "Canvas.h"
using namespace std;

double map(double input, double input_start, double input_end, double output_start, double output_end) {
	return (input - input_start) * (output_end - output_start) / (input_end - input_start) + output_start;
}

int main() {
	Canvas c = Canvas(839, 400);
	
	for (int i = 0; i < c.width; ++i) {
		int y = sin(i * 0.03) * 100 + 200;
		float r = y < 200 ? map(y, 200, 100, 0, 1) : map(y, 200, 300, 0, 1);
		c.writePixel(i, y, Color(r, 0.1, 0.4));
	}
	vector<string> ppm = canvasToPPM(&c);
	ofstream ppmFile;
	ppmFile.open("render.ppm");
	
	for (int i = 0; i < ppm.size(); ++i) {
		ppmFile << ppm[i] << endl;
	}
	return 0;
}
