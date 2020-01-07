#pragma once
#include <iostream>


class Matrix {
private:
	float** data;
	int size;

public:
	Matrix(int size);
	void rowOne(float a, float b);
	void rowOne(float a, float b, float c);
	void rowOne(float a, float b, float c, float d);
	void rowTwo(float a, float b);
	void rowTwo(float a, float b, float c);
	void rowTwo(float a, float b, float c, float d);
	void rowThree(float a, float b, float c);
	void rowThree(float a, float b, float c, float d);
	void rowFour(float a, float b, float c, float d);

	float& operator()(int index1, int index2);
};