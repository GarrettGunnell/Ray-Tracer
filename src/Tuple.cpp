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

bool equal(float a, float b) {
	return abs(a - b) < 0.00001;
}

bool operator== (const Tuple& p1, const Tuple& p2) {
	return (equal(p1.x, p2.x) &&
		equal(p1.y, p2.y) &&
		equal(p1.z, p2.z) &&
		equal(p1.w, p2.w));
}

bool operator!= (const Tuple& p1, const Tuple& p2) {
	return !(p1 == p2);
}

Tuple operator+ (const Tuple& p1, const Tuple& p2) {
	return Tuple(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z, p1.w + p2.w);
}

Tuple operator- (const Tuple& p1, const Tuple& p2) {
	return Tuple(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, p1.w - p2.w);
}

Tuple operator- (const Tuple& p) {
	return Tuple(0 - p.x, 0 - p.y, 0 - p.z, 0 - p.w);
}