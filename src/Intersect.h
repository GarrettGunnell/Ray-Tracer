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
};

vector<Intersection> intersect(Object* s, Ray r);
