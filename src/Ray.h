#pragma once
#include "Tuple.h"

class Ray {
public:
	Tuple origin;
	Tuple direction;

	Ray(Tuple origin, Tuple direction);
};