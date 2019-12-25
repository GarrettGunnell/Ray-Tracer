#include "Tuple.h"

Tuple::Tuple(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

bool Tuple::isPoint() {
	return this->w == 1.0;
}

bool Tuple::isVector() {
	return this->w == 0.0;
}

Tuple* point(float x, float y, float z) {
	Tuple* point = new Tuple(x, y, z, 1.0f);
	return point;
}

Tuple* vector(float x, float y, float z) {
	Tuple* vector = new Tuple(x, y, z, 0.0f);
	return vector;
}