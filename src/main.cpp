#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
using namespace std;

int main() {
	Canvas c = Canvas(10, 20);

	cout << c.pixels[5][10].red << endl;
	return 0;
}