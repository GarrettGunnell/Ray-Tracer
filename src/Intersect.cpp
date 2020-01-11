#include "Intersect.h"

using namespace std;

vector<float> intersect(Sphere s, Ray r) {
	vector<float> xs;

	Tuple sphereToRay = r.origin - Point(0, 0, 0);
	float a = dot(r.direction, r.direction);
	float b = 2 * dot(r.direction, sphereToRay);
	float c = dot(sphereToRay, sphereToRay) - 1;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return xs;
	}

	float t1 = (-b - float(sqrt(discriminant))) / (2 * a);
	float t2 = (-b + float(sqrt(discriminant))) / (2 * a);
	xs.push_back(t1);
	xs.push_back(t2);

	return xs;
}