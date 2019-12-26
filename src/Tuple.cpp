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

float Tuple::magnitude() {
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
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

Tuple* normalize(Tuple* p) {
	Tuple* x = new Tuple(p->x / p->magnitude(),
		p->y / p->magnitude(),
		p->z / p->magnitude(),
		p->w / p->magnitude());

	return x;
}

float dot(Tuple* p1, Tuple* p2) {
	return (p1->x * p2->x +
		p1->y * p2->y +
		p1->z * p2->z +
		p1->w * p2->w);
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

Tuple operator* (const Tuple& p, const float scalar) {
	return Tuple(p.x * scalar, p.y * scalar, p.z * scalar, p.w * scalar);
}

Tuple operator/ (const Tuple& p, const float scalar) {
	return Tuple(p.x / scalar, p.y / scalar, p.z / scalar, p.w / scalar);
}

Tuple operator- (const Tuple& p) {
	return Tuple(0 - p.x, 0 - p.y, 0 - p.z, 0 - p.w);
}