#pragma once
#include "Tuple.h"
#include "Matrix.h"

class Ray {
public:
	Tuple origin;
	Tuple direction;

	Ray(Tuple origin, Tuple direction);
	Tuple positionAt(float t);
};

Ray transform(Ray r, Matrix m);