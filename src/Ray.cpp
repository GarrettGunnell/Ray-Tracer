#include "Ray.h"

Ray::Ray(Tuple origin, Tuple direction) {
	this->origin = origin;
	this->direction = direction;
}

Tuple Ray::positionAt(float t) {
	return this->origin + this->direction * t;
}

Ray transform(Ray r, Matrix m) {
	Ray newR = Ray(m * r.origin, m * r.direction);
	return newR;
}