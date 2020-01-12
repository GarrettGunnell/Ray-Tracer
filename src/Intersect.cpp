#include "Intersect.h"

using namespace std;

Intersection::Intersection(float t, Object* o) {
	this->t = t;
	this->object = o;
}

Intersection::Intersection(float t) {
	this->t = t;
	this->object = NULL;
}

vector<Intersection> intersect(Object* s, Ray r) {
	vector<Intersection> xs;
	Ray r2 = transform(r, inverse(s->transform));

	Tuple sphereToRay = r2.origin - Point(0, 0, 0);
	float a = dot(r2.direction, r2.direction);
	float b = 2 * dot(r2.direction, sphereToRay);
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

Intersection hit(vector<Intersection> xs) {
	Intersection inter = Intersection(-1);

	for (int i = 0; i < xs.size(); ++i) {
		if (xs[i].t < 0) {
			continue;
		}
		else if (inter.t < 0) {
			inter = xs[i];
		}
		else if (xs[i].t < inter.t) {
			inter = xs[i];
		}
	}

	if (inter.t < 0) {
		return NULL;
	}

	return inter;
}

bool operator== (const Intersection& o1, const Intersection& o2) {
	return (o1.t == o2.t) && (o1.object == o2.object);
}