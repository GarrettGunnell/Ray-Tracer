#pragma once
#include <iostream>
#include "Tuple.h"
#include <vector>

using namespace std;


class Matrix {
private:
	vector<vector<float>> data;

public:
	int size;
	Matrix();
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

	bool invertible();

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
float cofactor(Matrix M, int row, int col);
Matrix subMatrix(Matrix M, int row, int col);
Matrix inverse(Matrix M);

Matrix Translation(float x, float y, float z);
Matrix Scaling(float x, float y, float z);
Matrix RotationX(float radian);
Matrix RotationY(float radian);
Matrix RotationZ(float radian);
Matrix Shearing(float xy, float xz, float yx, float yz, float zx, float zy);