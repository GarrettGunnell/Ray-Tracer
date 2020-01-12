#pragma once
#include "Matrix.h"

class Object {
public:
	int id;
	Matrix transform;

	friend bool operator== (const Object& o1, const Object& o2);
};