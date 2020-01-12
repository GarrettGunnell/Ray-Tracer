#include "Object.h"


bool operator== (const Object& o1, const Object& o2) {
	return o1.id == o2.id;
}