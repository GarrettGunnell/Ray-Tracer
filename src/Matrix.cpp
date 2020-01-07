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