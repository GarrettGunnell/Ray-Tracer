#include "Intersect.h"

using namespace std;

vector<float> intersect(Sphere s, Ray r) {

}

float discriminant(Ray r) {
	Tuple sphereToRay = r.origin - Point(0, 0, 0);
	float a = dot(r.direction, r.direction);
	float b = 2 * dot(r.direction, sphereToRay);
	float c = dot(sphereToRay, sphereToRay) - 1;

	return b * b - 4 * a * c;
}