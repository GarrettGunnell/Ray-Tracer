#include <iostream>
#include "Tuple.h"
using namespace std;

int main() {
	Tuple* a = vector(1, 2, 3);
	Tuple* b = vector(2, 3, 4);
	Tuple* crossab = cross(b, a);

	cout << crossab->x << ", " << crossab->y << ", " << crossab->z << endl;
	return 0;
}