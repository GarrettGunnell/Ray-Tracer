#include <iostream>
#include "Tuple.h"
#include "Canvas.h"
using namespace std;

int main() {
	Canvas c = Canvas(10, 20);
	string s = "P3\n5 3\n255";
	cout << s << endl;
	return 0;
}