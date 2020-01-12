#include <iostream>
#include <fstream>
#include <math.h>
#include "Tuple.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "Object.h"
#include "Sphere.h"
#include "Intersect.h"
using namespace std;

double map(double input, double input_start, double input_end, double output_start, double output_end) {
	return (input - input_start) * (output_end - output_start) / (input_end - input_start) + output_start;
}

int main() {
	
	int width = 839;
	int height = 400;
	Canvas c = Canvas(width, height);
	Sphere s = Sphere();
	s.transform = Translation(width / 2, height / 2, 0);
	Matrix S = Scaling(100, 100, 100);
	s.transform = s.transform * S;
	float count = 0;
	float total = width * height;
	float progress = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			++count;
			progress = count / total;
			cout << progress << endl;
			Ray r = Ray(Point(x, y, -5), Vector(0, 0, 1));
			vector<Intersection> xs = intersect(&s, r);
			Color color = xs.size() > 0 ? Color(1, 0, 0) : Color(0, 0, 0);
			c.writePixel(x, y, color);
		}
	}

	vector<string> ppm = canvasToPPM(&c);
	ofstream ppmFile;
	ppmFile.open("render.ppm");
	
	count = 0;
	for (int i = 0; i < ppm.size(); ++i) {
		++count;
		progress = count / ppm.size();
		cout << progress << endl;
		ppmFile << ppm[i] << endl;
	}
	return 0;
}
