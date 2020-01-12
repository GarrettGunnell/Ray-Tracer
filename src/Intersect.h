#pragma once
#include <vector>
#include "Sphere.h"
#include "Object.h"
#include "Ray.h"
#include "Tuple.h"

using namespace std;

struct Intersection {
	float t;
	Object* object;

	Intersection(float t, Object* o);
	Intersection(float t);

	friend bool operator== (const Intersection& o1, const Intersection& o2);
};

vector<Intersection> intersect(Object* s, Ray r);
Intersection hit(vector<Intersection> xs);
