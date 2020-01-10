#pragma once
#include <vector>
#include "Sphere.h"
#include "Ray.h"
#include "Tuple.h"

using namespace std;

vector<float> intersect(Sphere s, Ray r);

float discriminant(Ray r);