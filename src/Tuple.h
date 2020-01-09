#pragma once
#include <cstdlib>

class Tuple {
public:
	float x;
	float y;
	float z;
	float w;

	Tuple(float x, float y, float z, float w);
	bool isPoint();
	bool isVector();
	float magnitude();

	friend bool operator== (const Tuple& p1, const Tuple& p2);
	friend bool operator!= (const Tuple& p1, const Tuple& p2);
	friend Tuple operator+ (const Tuple& p1, const Tuple& p2);
	friend Tuple operator* (const Tuple& p, const float scalar);
	friend Tuple operator/ (const Tuple& p, const float scalar);
	friend Tuple operator- (const Tuple& p1, const Tuple& p2);
	friend Tuple operator- (const Tuple& p);
};

Tuple Point(float x, float y, float z);
Tuple Vector(float x, float y, float z);
Tuple normalize(Tuple p);
float dot(Tuple p1, Tuple p2);
Tuple cross(Tuple v1, Tuple v2);
bool equal(float a, float b);
