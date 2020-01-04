#include <iostream>
#include <fstream>
#include "Tuple.h"
#include "Canvas.h"
using namespace std;

int main() {
	Canvas c = Canvas(6, 6);
	Color c1 = Color(1.5, 0, 0);
	Color c2 = Color(0, 0.5, 0);
	Color c3 = Color(-0.5, 0, 1);
	c.writePixel(0, 0, c1);
	c.writePixel(2, 1, c2);
	c.writePixel(4, 2, c3);
	vector<string> ppm = canvasToPPM(&c);
	ofstream ppmFile;
	ppmFile.open("render.ppm");
	
	for (int i = 0; i < ppm.size(); ++i) {
		ppmFile << ppm[i] << endl;
	}
	return 0;
}