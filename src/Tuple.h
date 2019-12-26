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

	friend bool operator== (const Tuple& p1, const Tuple& p2);
	friend bool operator!= (const Tuple& p1, const Tuple& p2);
	friend Tuple operator+ (const Tuple& p1, const Tuple& p2);
	friend Tuple operator- (const Tuple& p1, const Tuple& p2);
	friend Tuple operator- (const Tuple& p);
};

Tuple* point(float x, float y, float z);
Tuple* vector(float x, float y, float z);
bool equal(float a, float b);
