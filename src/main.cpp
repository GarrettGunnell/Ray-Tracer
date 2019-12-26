#include <iostream>
#include "Tuple.h"
using namespace std;

int main() {
	Tuple* v = vector(1, 2, 3);
	Tuple* nv = normalize(v);
	cout << nv->magnitude();
	return 0;
}