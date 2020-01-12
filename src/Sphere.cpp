#include "Sphere.h"

Sphere::Sphere() {
	srand(rand() % 1000);
	this->id = rand() % 10000;
}
