#include "Matrix.h"

Matrix::Matrix() {};

Matrix::Matrix(int size) {
	this->size = size;
	for (int i = 0; i < size; ++i) {
		vector<float> v;
		for (int j = 0; j < size; ++j) {
			v.push_back(0);
		}
		this->data.push_back(v);
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

bool Matrix::invertible() {
	return determinant(*this) != 0;
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

Matrix IdentityMatrix() {
	Matrix M = Matrix(4);
	M.rowOne(1, 0, 0, 0);
	M.rowTwo(0, 1, 0, 0);
	M.rowThree(0, 0, 1, 0);
	M.rowFour(0, 0, 0, 1);

	return M;
}

Matrix transpose(Matrix M) {
	Matrix A = Matrix(4);
	A.rowOne(M(0, 0), M(1, 0), M(2, 0), M(3, 0));
	A.rowTwo(M(0, 1), M(1, 1), M(2, 1), M(3, 1));
	A.rowThree(M(0, 2), M(1, 2), M(2, 2), M(3, 2));
	A.rowFour(M(0, 3), M(1, 3), M(2, 3), M(3, 3));

	return A;
}

float determinant(Matrix M) {
	if (M.size == 2) {
		return M(0, 0) * M(1, 1) - M(0, 1) * M(1, 0);
	}

	float det = 0;
	for (int col = 0; col < M.size; ++col) {
		det += M(0, col) * cofactor(M, 0, col);
	}

	return det;
}

float minor(Matrix M, int row, int col) {
	return determinant(subMatrix(M, row, col));
}

float cofactor(Matrix M, int row, int col) {
	float x = (row + col) % 2 == 0 ? minor(M, row, col) : -minor(M, row, col);
	return x;
}

Matrix subMatrix(Matrix M, int row, int col) {
	Matrix A = Matrix(M.size - 1);
	int curRow = 0;

	for (int i = 0; i < M.size; ++i) {
		if (i == row) {
			continue;
		}
		int curCol = 0;
		for (int j = 0; j < M.size; ++j) {
			if (j == col) {
				continue;
			}
			A(curRow, curCol) = M(i, j);
			curCol++;
		}
		curRow++;
	}

	return A;
}

Matrix inverse(Matrix M) {
	float det = determinant(M);

	if (det == 0) {
		std::cout << "Matrix has no inverse" << std::endl;
		exit(0);
	}

	Matrix A = Matrix(M.size);

	for (int row = 0; row < M.size; ++row) {
		for (int col = 0; col < M.size; ++col) {
			float c = cofactor(M, row, col);

			A(col, row) = c / det;
		}
	}

	return A;
}

Matrix Translation(float x, float y, float z) {
	Matrix M = IdentityMatrix();
	M(0, 3) = x;
	M(1, 3) = y;
	M(2, 3) = z;

	return M;
}

Matrix Scaling(float x, float y, float z) {
	Matrix M = IdentityMatrix();
	M(0, 0) = x;
	M(1, 1) = y;
	M(2, 2) = z;

	return M;
}

Matrix RotationX(float radian) {
	Matrix M = IdentityMatrix();
	M(1, 1) = cos(radian);
	M(1, 2) = -sin(radian);
	M(2, 1) = sin(radian);
	M(2, 2) = cos(radian);

	return M;
}

Matrix RotationY(float radian) {
	Matrix M = IdentityMatrix();
	M(0, 0) = cos(radian);
	M(0, 2) = sin(radian);
	M(2, 0) = -sin(radian);
	M(2, 2) = cos(radian);

	return M;
}

Matrix RotationZ(float radian) {
	Matrix M = IdentityMatrix();
	M(0, 0) = cos(radian);
	M(0, 1) = -sin(radian);
	M(1, 0) = sin(radian);
	M(1, 1) = cos(radian);

	return M;
}

Matrix Shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
	Matrix M = IdentityMatrix();
	M(0, 1) = xy;
	M(0, 2) = xz;
	M(1, 0) = yx;
	M(1, 2) = yz;
	M(2, 0) = zx;
	M(2, 1) = zy;

	return M;
}