#include "Matrix.h"

Matrix::Matrix(int size) {
	this->size = size;
	this->data = new float*[size];
	for (int i = 0; i < size; ++i) {
		this->data[i] = new float[size];
	}
}

void Matrix::rowOne(float a, float b) {
	this->data[0][0] = a;
	this->data[0][1] = b;
}

void Matrix::rowOne(float a, float b, float c) {
	this->data[0][0] = a;
	this->data[0][1] = b;
	this->data[0][2] = c;
}

void Matrix::rowOne(float a, float b, float c, float d) {
	this->data[0][0] = a;
	this->data[0][1] = b;
	this->data[0][2] = c;
	this->data[0][3] = d;
}

void Matrix::rowTwo(float a, float b) {
	this->data[1][0] = a;
	this->data[1][1] = b;
}

void Matrix::rowTwo(float a, float b, float c) {
	this->data[1][0] = a;
	this->data[1][1] = b;
	this->data[1][2] = c;
}

void Matrix::rowTwo(float a, float b, float c, float d) {
	this->data[1][0] = a;
	this->data[1][1] = b;
	this->data[1][2] = c;
	this->data[1][3] = d;
}

void Matrix::rowThree(float a, float b, float c) {
	this->data[2][0] = a;
	this->data[2][1] = b;
	this->data[2][2] = c;
}

void Matrix::rowThree(float a, float b, float c, float d) {
	this->data[2][0] = a;
	this->data[2][1] = b;
	this->data[2][2] = c;
	this->data[2][3] = d;
}
void Matrix::rowFour(float a, float b, float c, float d) {
	this->data[3][0] = a;
	this->data[3][1] = b;
	this->data[3][2] = c;
	this->data[3][3] = d;
}

float& Matrix::operator()(int index1, int index2) {
	if (index1 < 0 || index1 >= size || index2 < 0 || index2 >= size) {
		std::cout << "Index out of bounds.";
		exit(0);
	}
	return this->data[index1][index2];
}

bool operator== (Matrix& A, Matrix& B) {
	bool isEqual = false;
	if (A.size == B.size) {
		isEqual = true;
		for (int i = 0; i < A.size; ++i) {
			if (!isEqual) {
				break;
			}
			for (int j = 0; j < A.size; ++j) {
				if (!equal(A(i, j), B(i, j))) {
					isEqual = false;
					break;
				}
			}
		}
	}

	return isEqual;
}

bool operator!= (Matrix& A, Matrix& B) {
	return !(A == B);
}

Matrix operator* (Matrix& A, Matrix& B) {
	if (A.size != 4 || B.size != 4) {
		std::cout << "Multiplication on Matrix not of size 4";
		exit(0);
	}

	Matrix C = Matrix(4);

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			C(row, col) = A(row, 0) * B(0, col) +
						  A(row, 1) * B(1, col) +
						  A(row, 2) * B(2, col) +
						  A(row, 3) * B(3, col);
		}
	}

	return C;
}

Tuple operator* (Matrix& A, Tuple& b) {
	Matrix M = Matrix(4);

	for (int row = 0; row < 4; ++row) {
		M(row, 0) = A(row, 0) * b.x +
					A(row, 1) * b.y +
					A(row, 2) * b.z +
					A(row, 3) * b.w;
	}

	return Tuple(M(0, 0), M(1, 0), M(2, 0), M(3, 0));
}