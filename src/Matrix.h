#pragma once
#include <iostream>
#include "Tuple.h"


class Matrix {
private:
	float** data;

public:
	int size;
	Matrix(int size);
	void row(int row, float a, float b);
	void row(int row, float a, float b, float c);
	void rowOne(float a, float b);
	void rowOne(float a, float b, float c);
	void rowOne(float a, float b, float c, float d);
	void rowTwo(float a, float b);
	void rowTwo(float a, float b, float c);
	void rowTwo(float a, float b, float c, float d);
	void rowThree(float a, float b, float c);
	void rowThree(float a, float b, float c, float d);
	void rowFour(float a, float b, float c, float d);

	float& operator()(const int index1, const int index2);

	friend bool operator== (Matrix& A, Matrix& B);
	friend bool operator!= (Matrix& A, Matrix& B);
	friend Matrix operator* (Matrix& A, Matrix& B);
	friend Tuple operator* (Matrix& A, Tuple& b);
};

Matrix IdentityMatrix();
Matrix transpose(Matrix M);
float determinant(Matrix M);
float minor(Matrix M, int row, int col);
Matrix subMatrix(Matrix M, int row, int col);