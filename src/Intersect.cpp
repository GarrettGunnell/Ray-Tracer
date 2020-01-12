#include "Intersect.h"

using namespace std;

Intersection::Intersection(float t, Object* o) {
	this->t = t;
	this->object = o;
}

vector<Intersection> intersect(Object* s, Ray r) {
	vector<Intersection> xs;

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
	xs.push_back(Intersection(t1, s));
	xs.push_back(Intersection(t2, s));

	return xs;
}