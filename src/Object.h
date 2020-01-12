#pragma once

class Object {
public:
	int id;

	friend bool operator== (const Object& o1, const Object& o2);
};