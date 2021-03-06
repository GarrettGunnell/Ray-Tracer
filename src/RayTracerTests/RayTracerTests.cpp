#include "pch.h"
#include "CppUnitTest.h"
#include <cstdlib>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../Tuple.cpp"
#include "../Color.cpp"
#include "../Canvas.cpp"
#include "../Matrix.cpp"
#include "../Ray.cpp"
#include "../Sphere.cpp"
#include "../Intersect.cpp"
#include "../Object.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace RayTracerTests {

	TEST_CLASS(Tuples) {

	public:
		TEST_METHOD(ATupleIsAPoint) {
			//A tuple with w = 1.0 is a Point
			float x = 4.3f;
			float y = -4.2f;
			float z = 3.1f;
			float w = 1.0f;
			Tuple a = Tuple(x, y, z, w);
			Assert::AreEqual(x, a.x);
			Assert::AreEqual(y, a.y);
			Assert::AreEqual(z, a.z);
			Assert::AreEqual(w, a.w);
			Assert::IsTrue(a.isPoint());
			Assert::IsFalse(a.isVector());
		}

		TEST_METHOD(ATupleIsAVector) {
			//A tuple with w = 0 is a Vector
			float x = 4.3f;
			float y = -4.2f;
			float z = 3.1f;
			float w = 0.0f;
			Tuple a = Tuple(x, y, z, w);
			Assert::AreEqual(x, a.x);
			Assert::AreEqual(y, a.y);
			Assert::AreEqual(z, a.z);
			Assert::AreEqual(w, a.w);
			Assert::IsFalse(a.isPoint());
			Assert::IsTrue(a.isVector());
		}

		TEST_METHOD(APointIsAPoint) {
			Tuple a = Point(4, -4, 3);
			Tuple b = Tuple(4, -4, 3, 1);
			Assert::AreEqual(a.x, b.x);
			Assert::AreEqual(a.y, b.y);
			Assert::AreEqual(a.z, b.z);
			Assert::AreEqual(a.w, b.w);
		}

		TEST_METHOD(AVectorIsAVector) {
			Tuple a = Vector(4, -4, 3);
			Tuple b = Tuple(4, -4, 3, 0);
			Assert::AreEqual(a.x, b.x);
			Assert::AreEqual(a.y, b.y);
			Assert::AreEqual(a.z, b.z);
			Assert::AreEqual(a.w, b.w);
		}

		TEST_METHOD(TupleEquality) {
			Tuple a = Tuple(1.0f, 1.0f, 1.0f, 0.0f);
			Tuple b = Tuple(1.0f, 1.0f, 1.0f, 0.0f);
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(TupleInequality) {
			Tuple a = Tuple(1.0f, 1.0f, 1.0f, 0.0f);
			Tuple b = Tuple(1.0f, 1.0f, 1.0f, 1.0f);
			Assert::IsTrue(a != b);
		}

		TEST_METHOD(TupleAddition) {
			Tuple a = Tuple(3, -2, 5, 1);
			Tuple b = Tuple(-2, 3, 1, 0);
			Tuple c = Tuple(1, 1, 6, 1);
			Assert::IsTrue((a + b) == c);
		}

		TEST_METHOD(PointSubtraction) {
			//A Point minus a Point is a Vector
			Tuple a = Point(3, 2, 1);
			Tuple b = Point(5, 6, 7);
			Tuple c = Vector(-2, -4, -6);
			Assert::IsTrue((a - b) == c);
		}

		TEST_METHOD(PointVectorSubtraction) {
			//A Point minus a Vector is a Point
			Tuple a = Point(3, 2, 1);
			Tuple b = Vector(5, 6, 7);
			Tuple c = Point(-2, -4, -6);
			Assert::IsTrue((a - b) == c);
		}

		TEST_METHOD(VectorSubtraction) {
			//A Vector minus a Vector is a Vector
			Tuple a = Vector(3, 2, 1);
			Tuple b = Vector(5, 6, 7);
			Tuple c = Vector(-2, -4, -6);
			Assert::IsTrue((a - b) == c);
		}

		TEST_METHOD(SubtractingFromZeroVector) {
			Tuple zero = Vector(0, 0, 0);
			Tuple v = Vector(1, -2, 3);
			Tuple vNegation = Vector(-1, 2, -3);
			Assert::IsTrue((zero - v) == vNegation);
		}

		TEST_METHOD(TupleNegation) {
			//A tuple subtracted from the zero Vector is negated
			Tuple a = Tuple(1, -2, 3, 4);
			Tuple b = Tuple(-1, 2, -3, -4);
			Assert::IsTrue(-a == b);
		}

		TEST_METHOD(MultiplyingByAScalar) {
			Tuple a = Tuple(1, -2, 3, -4);
			Tuple b = Tuple(3.5, -7, 10.5, -14);
			Assert::IsTrue(a * 3.5 == b);
		}

		TEST_METHOD(MultiplyingByAFraction) {
			Tuple a = Tuple(1, -2, 3, -4);
			Tuple b = Tuple(0.5f, -1, 1.5f, -2);
			Assert::IsTrue(a * 0.5 == b);
		}

		TEST_METHOD(TupleDivision) {
			Tuple a = Tuple(1, -2, 3, -4);
			Tuple b = Tuple(0.5f, -1, 1.5f, -2);
			Assert::IsTrue(a / 2 == b);
		}

		TEST_METHOD(Magnitude) {
			Tuple v1 = Vector(1, 0, 0);
			float m = v1.magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple v2 = Vector(0, 1, 0);
			m = v2.magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple v3 = Vector(0, 0, 1);
			m = v3.magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple v4 = Vector(1, 2, 3);
			m = v4.magnitude();
			Assert::AreEqual(m, float(sqrt(14)));

			Tuple v5 = Vector(-1, -2, -3);
			m = v5.magnitude();
			Assert::AreEqual(m, float(sqrt(14)));
		}

		TEST_METHOD(NormalizingAVector) {
			Tuple v = Vector(4, 0, 0);
			Tuple nv = normalize(v);
			Tuple uv = Vector(1, 0, 0);
			Assert::IsTrue(nv == uv);

			v = Vector(1, 2, 3);
			nv = normalize(v);
			uv = Vector(1 / float(sqrt(14)), 2 / float(sqrt(14)), 3 / float(sqrt(14)));
			Assert::IsTrue(nv == uv);
		}

		TEST_METHOD(MagnitudeOfNormalizedVector) {
			Tuple v = Vector(1, 2, 3);
			Tuple nv = normalize(v);
			Assert::IsTrue(equal(nv.magnitude(), 1.0f));
		}

		TEST_METHOD(DotProductOfTwoTuples) {
			Tuple a = Vector(1, 2, 3);
			Tuple b = Vector(2, 3, 4);
			Assert::AreEqual(dot(a, b), 20.0f);
		}

		TEST_METHOD(CrossProductOfTwoVectors) {
			Tuple a = Vector(1, 2, 3);
			Tuple b = Vector(2, 3, 4);
			Tuple crossab = Vector(-1, 2, -1);
			Tuple crossba = Vector(1, -2, 1);
			Tuple crossabf = cross(a, b);
			Tuple crossbaf = cross(b, a);
			Assert::IsTrue(crossabf == crossab);
			Assert::IsTrue(crossbaf == crossba);
		}
	};

	TEST_CLASS(Colors) {
	public:
		
		TEST_METHOD(AColorExists) {
			Color c = Color(-0.5f, 1.7f, 0.4f);

			Assert::AreEqual(c.red, -0.5f);
			Assert::AreEqual(c.blue, 0.4f);
			Assert::AreEqual(c.green, 1.7f);
		}

		TEST_METHOD(ColorAddition) {
			Color c1 = Color(0.9f, 0.75f, 0.6f);
			Color c2 = Color(0.7f, 0.25f, 0.1f);
			Color c3 = Color(1.6f, 1.0f, 0.7f);

			Assert::IsTrue(c1 + c2 == c3);
		}

		TEST_METHOD(ColorSubtraction) {
			Color c1 = Color(0.9f, 0.75f, 0.6f);
			Color c2 = Color(0.7f, 0.25f, 0.1f);
			Color c3 = Color(0.2f, 0.5f, 0.5f);

			Assert::IsTrue(c1 - c2 == c3);
		}

		TEST_METHOD(ColorScalarMultiplication) {
			Color c1 = Color(0.2f, 0.4f, 0.3f);
			Color c2 = Color(0.4f, 0.8f, 0.6f);

			Assert::IsTrue(c1 * 2 == c2);
		}

		TEST_METHOD(ColorMultiplication) {
			Color c1 = Color(1.0f, 0.4f, 1.0f);
			Color c2 = Color(0.9f, 0.1f, 0.2f);
			Color c3 = Color(0.9f, 0.04f, 0.2f);

			Assert::IsTrue(c1 * c2 == c3);
		}
	};

	TEST_CLASS(CanvasTests) {
	public:

		TEST_METHOD(ACanvasExists) {
			Canvas c = Canvas(10, 20);
			
			Assert::AreEqual(c.width, 10);
			Assert::AreEqual(c.height, 20);

			Color c1 = Color(0, 0, 0);
			for (int i = 0; i < c.height; ++i) {
				for (int j = 0; j < c.width; ++j) {
					Assert::IsTrue(c.pixels[i][j] == c1);
				}
			}
		}

		TEST_METHOD(WritingPixelToCanvas) {
			Canvas c = Canvas(10, 20);
			Color red = Color(1, 0, 0);

			c.writePixel(2, 3, red);
			Assert::IsTrue(c.pixelAt(2, 3) == red);
		}

		TEST_METHOD(PPM_Header) {
			Canvas c = Canvas(5, 3);
			string s1 = "P3";
			string s2 = "5 3";
			string s3 = "255";
			Assert::AreEqual(canvasToPPM(&c)[0], s1);
			Assert::AreEqual(canvasToPPM(&c)[1], s2);
			Assert::AreEqual(canvasToPPM(&c)[2], s3);
		}

		TEST_METHOD(PPM_Body) {
			Canvas c = Canvas(5, 3);
			Color c1 = Color(1.5, 0, 0);
			Color c2 = Color(0, 0.5, 0);
			Color c3 = Color(-0.5, 0, 1);
			c.writePixel(0, 0, c1);
			c.writePixel(2, 1, c2);
			c.writePixel(4, 2, c3);
			vector<string> ppm = canvasToPPM(&c);

			string s1 = "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
			string s2 = "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0";
			string s3 = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
			Assert::AreEqual(ppm[3], s1);
			Assert::AreEqual(ppm[4], s2);
			Assert::AreEqual(ppm[5], s3);
		}

		TEST_METHOD(SplitLongLines) {
			Canvas c = Canvas(10, 2);
			for (int i = 0; i < c.height; ++i) {
				for (int j = 0; j < c.width; ++j) {
					c.writePixel(j, i, Color(1, 0.8f, 0.6f));
				}
			}

			vector<string> ppm = canvasToPPM(&c);
			string s1 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204";
			string s2 = "153 255 204 153 255 204 153 255 204 153 255 204 153";
			string s3 = "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204";
			string s4 = "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
			Assert::AreEqual(ppm[3], s1);
			Assert::AreEqual(ppm[4], s2);
			Assert::AreEqual(ppm[5], s3);
			Assert::AreEqual(ppm[6], s4);
		}
	};

	TEST_CLASS(Matrices) {
	public:

		TEST_METHOD(AMatrixExists) {
			Matrix M = Matrix(4);

			M.rowOne(1, 2, 3, 4);
			M.rowTwo(5.5f, 6.5f, 7.5f, 8.5f);
			M.rowThree(9, 10, 11, 12);
			M.rowFour(13.5f, 14.5f, 15.5f, 16.5f);
			
			Assert::AreEqual(M(0, 0), 1.0f);
			Assert::AreEqual(M(0, 3), 4.0f);
			Assert::AreEqual(M(1, 0), 5.5f);
			Assert::AreEqual(M(1, 2), 7.5f);
			Assert::AreEqual(M(2, 2), 11.0f);
			Assert::AreEqual(M(3, 0), 13.5f);
			Assert::AreEqual(M(3, 2), 15.5f);
		}

		TEST_METHOD(A2DMatrixExists) {
			Matrix M = Matrix(2);

			M.rowOne(-3, 5);
			M.rowTwo(1, -2);

			Assert::AreEqual(M(0, 0), -3.0f);
			Assert::AreEqual(M(0, 1), 5.0f);
			Assert::AreEqual(M(1, 0), 1.0f);
			Assert::AreEqual(M(1, 1), -2.0f);
		}

		TEST_METHOD(A3DMatrixExists) {
			Matrix M = Matrix(3);

			M.rowOne(-3, 5, 0);
			M.rowTwo(1, -2, -7);
			M.rowThree(0, 1, 1);

			Assert::AreEqual(M(0, 0), -3.0f);
			Assert::AreEqual(M(1, 1), -2.0f);
			Assert::AreEqual(M(2, 2), 1.0f);
		}

		TEST_METHOD(MatrixEquality) {
			Matrix A = Matrix(4);
			A.rowOne(1, 2, 3, 4);
			A.rowTwo(5, 6, 7, 8);
			A.rowThree(9, 8, 7, 6);
			A.rowFour(5, 4, 3, 2);

			Matrix B = Matrix(4);
			B.rowOne(1, 2, 3, 4);
			B.rowTwo(5, 6, 7, 8);
			B.rowThree(9, 8, 7, 6);
			B.rowFour(5, 4, 3, 2);

			Assert::IsTrue(A == B);
		}

		TEST_METHOD(MatrixInequality) {
			Matrix A = Matrix(4);
			A.rowOne(1, 2, 3, 4);
			A.rowTwo(5, 6, 7, 8);
			A.rowThree(9, 8, 7, 6);
			A.rowFour(5, 4, 3, 2);

			Matrix B = Matrix(4);
			B.rowOne(1, 2, 3, 4);
			B.rowTwo(5, 6, 7, 8);
			B.rowThree(9, 8, 7, 6);
			B.rowFour(1, 1, 1, 1);

			Assert::IsTrue(A != B);
		}

		TEST_METHOD(MatrixMultiplication) {
			Matrix A = Matrix(4);
			A.rowOne(1, 2, 3, 4);
			A.rowTwo(5, 6, 7, 8);
			A.rowThree(9, 8, 7, 6);
			A.rowFour(5, 4, 3, 2);

			Matrix B = Matrix(4);
			B.rowOne(-2, 1, 2, 3);
			B.rowTwo(3, 2, 1, -1);
			B.rowThree(4, 3, 6, 5);
			B.rowFour(1, 2, 7, 8);

			Matrix C = Matrix(4);
			C.rowOne(20, 22, 50, 48);
			C.rowTwo(44, 54, 114, 108);
			C.rowThree(40, 58, 110, 102);
			C.rowFour(16, 26, 46, 42);

			Assert::IsTrue(A * B == C);
		}

		TEST_METHOD(MatrixAndTupleMultiplication) {
			Matrix A = Matrix(4);
			A.rowOne(1, 2, 3, 4);
			A.rowTwo(2, 4, 4, 2);
			A.rowThree(8, 6, 4, 1);
			A.rowFour(0, 0, 0, 1);

			Tuple b = Tuple(1, 2, 3, 1);

			Assert::IsTrue(A * b == Tuple(18, 24, 33, 1));
		}

		TEST_METHOD(IdentityMatrixMultiplication) {
			Matrix A = Matrix(4);
			A.rowOne(0, 1, 2, 4);
			A.rowTwo(1, 2, 4, 8);
			A.rowThree(2, 4, 8, 16);
			A.rowFour(4, 8, 16, 32);

			Matrix IDENTITY_MATRIX = IdentityMatrix();
			Assert::IsTrue(A * IDENTITY_MATRIX == A);
		}

		TEST_METHOD(TransposeMatrix) {
			Matrix A = Matrix(4);
			A.rowOne(0, 9, 3, 0);
			A.rowTwo(9, 8, 0, 8);
			A.rowThree(1, 8, 5, 3);
			A.rowFour(0, 0, 5, 8);

			Matrix TA = Matrix(4);
			TA.rowOne(0, 9, 1, 0);
			TA.rowTwo(9, 8, 8, 0);
			TA.rowThree(3, 0, 5, 5);
			TA.rowFour(0, 8, 3, 8);

			Assert::IsTrue(transpose(A) == TA);
		}

		TEST_METHOD(MatrixDeterminant) {
			Matrix A = Matrix(2);
			A.rowOne(1, 5);
			A.rowTwo(-3, 2);

			Assert::AreEqual(determinant(A), 17.0f);
		}

		TEST_METHOD(SubmatrixOf3x3) {
			Matrix A = Matrix(3);
			A.rowOne(1, 5, 0);
			A.rowTwo(-3, 2, 7);
			A.rowThree(0, 6, -3);

			Matrix B = Matrix(2);
			B.rowOne(-3, 2);
			B.rowTwo(0, 6);

			Assert::IsTrue(subMatrix(A, 0, 2) == B);
		}

		TEST_METHOD(SubmatrixOf4x4) {
			Matrix A = Matrix(4);
			A.rowOne(-6, 1, 1, 6);
			A.rowTwo(-8, 5, 8, 6);
			A.rowThree(-1, 0, 8, 2);
			A.rowFour(-7, 1, -1, 1);

			Matrix B = Matrix(3);
			B.rowOne(-6, 1, 6);
			B.rowTwo(-8, 8, 6);
			B.rowThree(-7, -1, 1);

			Assert::IsTrue(subMatrix(A, 2, 1) == B);
		}

		TEST_METHOD(MatrixMinor) {
			Matrix A = Matrix(3);
			A.rowOne(3, 5, 0);
			A.rowTwo(2, -1, -7);
			A.rowThree(6, -1, 5);
			Matrix B = subMatrix(A, 1, 0);
			Assert::AreEqual(determinant(B), 25.0f);
			Assert::AreEqual(minor(A, 1, 0), 25.0f);
		}

		TEST_METHOD(ComputeCofactor) {
			Matrix A = Matrix(3);
			A.rowOne(3, 5, 0);
			A.rowTwo(2, -1, -7);
			A.rowThree(6, -1, 5);

			Assert::AreEqual(minor(A, 0, 0), -12.0f);
			Assert::AreEqual(cofactor(A, 0, 0), -12.0f);
			Assert::AreEqual(minor(A, 1, 0), 25.0f);
			Assert::AreEqual(cofactor(A, 1, 0), -25.0f);
		}

		TEST_METHOD(DeterminantOf3x3Matrix) {
			Matrix A = Matrix(3);
			A.rowOne(1, 2, 6);
			A.rowTwo(-5, 8, -4);
			A.rowThree(2, 6, 4);

			Assert::AreEqual(cofactor(A, 0, 0), 56.0f);
			Assert::AreEqual(cofactor(A, 0, 1), 12.0f);
			Assert::AreEqual(cofactor(A, 0, 2), -46.0f);
			Assert::AreEqual(determinant(A), -196.0f);
		}

		TEST_METHOD(DeterminantOf4x4Matrix) {
			Matrix A = Matrix(4);
			A.rowOne(-2, -8, 3, 5);
			A.rowTwo(-3, 1, 7, 3);
			A.rowThree(1, 2, -9, 6);
			A.rowFour(-6, 7, 7, -9);

			Assert::AreEqual(cofactor(A, 0, 0), 690.0f);
			Assert::AreEqual(cofactor(A, 0, 1), 447.0f);
			Assert::AreEqual(cofactor(A, 0, 2), 210.0f);
			Assert::AreEqual(cofactor(A, 0, 3), 51.0f);
			Assert::AreEqual(determinant(A), -4071.0f);
		}

		TEST_METHOD(MatrixInvertability) {
			Matrix A = Matrix(4);
			A.rowOne(6, 4, 4, 4);
			A.rowTwo(5, 5, 7, 6);
			A.rowThree(4, -9, 3, -7);
			A.rowFour(9, 1, 7, -6);
			
			Assert::IsTrue(A.invertible());

			Matrix B = Matrix(4);
			A.rowOne(-4, 2, -2, -3);
			A.rowTwo(9, 6, 2, 6);
			A.rowThree(0, -5, 1, -5);
			A.rowFour(0, 0, 0, 0);

			Assert::IsFalse(B.invertible());
		}

		TEST_METHOD(InverseMatrix) {
			Matrix A = Matrix(4);
			A.rowOne(-5, 2, 6, -8);
			A.rowTwo(1, -5, 1, 8);
			A.rowThree(7, 7, -6, -7);
			A.rowFour(1, -3, 7, 4);

			Matrix B = inverse(A);

			Assert::AreEqual(determinant(A), 532.0f);
			Assert::AreEqual(cofactor(A, 2, 3), -160.0f);
			Assert::AreEqual(B(3, 2), -160.0f / 532.0f);
			Assert::AreEqual(cofactor(A, 3, 2), 105.0f);
			Assert::AreEqual(B(2, 3), 105.0f / 532.0f);

			Matrix C = Matrix(4);
			C.rowOne(0.21805f, 0.45113f, 0.24060f, -0.04511f);
			C.rowTwo(-0.80827f, -1.45677f, -0.44361f, 0.52068f);
			C.rowThree(-0.07895f, -0.22368f, -0.05263f, 0.19737f);
			C.rowFour(-0.52256f, -0.81391f, -0.30075f, 0.30639f);

			Assert::IsTrue(B == C);
		}

		TEST_METHOD(MultiplyMatrixByInverse) {
			Matrix A = Matrix(4);
			A.rowOne(3, -9, 7, 3);
			A.rowTwo(3, -8, 2, -9);
			A.rowThree(-4, 4, 4, 1);
			A.rowFour(-6, 5, -1, 1);

			Matrix B = Matrix(4);
			B.rowOne(8, 2, 2, 2);
			B.rowTwo(3, -1, 7, 0);
			B.rowThree(7, 0, 5, 4);
			B.rowFour(6, -2, 0, 5);

			Matrix C = A * B;
			Assert::IsTrue(C * inverse(B) == A);
		}
	};

	TEST_CLASS(MatrixTransformations) {
	public:

		TEST_METHOD(Translations) {
			Matrix transform = Translation(5, -3, 2);
			Tuple p = Point(-3, 4, 5);

			Assert::IsTrue(transform * p == Point(2, 1, 7));
		}

		TEST_METHOD(InverseTranslation) {
			Matrix transform = Translation(5, -3, 2);
			Tuple p = Point(-3, 4, 5);
			Matrix inv = inverse(transform);

			Assert::IsTrue(inv * p == Point(-8, 7, 3));
		}

		TEST_METHOD(TranslationsAndVectors) {
			//A vector should not be affected by a translation
			Matrix transform = Translation(5, -3, 2);
			Tuple v = Vector(-3, 4, 5);

			Assert::IsTrue(transform * v == v);
		}

		TEST_METHOD(ScalingTransform) {
			Matrix transform = Scaling(2, 3, 4);
			Tuple p = Point(-4, 6, 8);

			Assert::IsTrue(transform * p == Point(-8, 18, 32));
		}

		TEST_METHOD(ScalingAndVectors) {
			Matrix transform = Scaling(2, 3, 4);
			Tuple v = Vector(-4, 6, 8);

			Assert::IsTrue(transform * v == Vector(-8, 18, 32));
		}

		TEST_METHOD(InverseScaling) {
			Matrix transform = Scaling(2, 3, 4);
			Matrix inv = inverse(transform);
			Tuple v = Vector(-4, 6, 8);

			Assert::IsTrue(inv * v == Vector(-2, 2, 2));
		}

		TEST_METHOD(Reflection) {
			Matrix transform = Scaling(-1, 1, 1);
			Tuple p = Point(2, 3, 4);

			Assert::IsTrue(transform * p == Point(-2, 3, 4));
		}

		TEST_METHOD(XRotation) {
			Tuple p = Point(0, 1, 0);
			Matrix halfQuarter = RotationX(float(M_PI / 4));
			Matrix fullQuarter = RotationX(float(M_PI / 2));

			Assert::IsTrue(halfQuarter * p == Point(0, float(sqrt(2) / 2), float(sqrt(2) / 2)));
			Assert::IsTrue(fullQuarter * p == Point(0, 0, 1));
		}

		TEST_METHOD(InverseXRotation) {
			Tuple p = Point(0, 1, 0);
			Matrix halfQuarter = inverse(RotationX(float(M_PI / 4)));
			Matrix fullQuarter = inverse(RotationX(float(M_PI / 2)));

			Assert::IsTrue(halfQuarter * p == Point(0, float(sqrt(2) / 2), float(-sqrt(2) / 2)));
			Assert::IsTrue(fullQuarter * p == Point(0, 0, -1));
		}

		TEST_METHOD(YRotation) {
			Tuple p = Point(0, 0, 1);
			Matrix halfQuarter = RotationY(float(M_PI / 4));
			Matrix fullQuarter = RotationY(float(M_PI / 2));

			Assert::IsTrue(halfQuarter * p == Point(float(sqrt(2) / 2), 0, float(sqrt(2) / 2)));
			Assert::IsTrue(fullQuarter * p == Point(1, 0, 0));
		}

		TEST_METHOD(ZRotation) {
			Tuple p = Point(0, 1, 0);
			Matrix halfQuarter = RotationZ(float(M_PI / 4));
			Matrix fullQuarter = RotationZ(float(M_PI / 2));

			Assert::IsTrue(halfQuarter * p == Point(float(-sqrt(2) / 2), float(sqrt(2) / 2), 0));
			Assert::IsTrue(fullQuarter * p == Point(-1, 0, 0));
		}

		TEST_METHOD(ShearingTransform) {
			Tuple p = Point(2, 3, 4);
			Matrix transform = Shearing(1, 0, 0, 0, 0, 0);

			Assert::IsTrue(transform * p == Point(5, 3, 4));

			transform = Shearing(0, 1, 0, 0, 0, 0);
			Assert::IsTrue(transform * p == Point(6, 3, 4));

			transform = Shearing(0, 0, 1, 0, 0, 0);
			Assert::IsTrue(transform * p == Point(2, 5, 4));

			transform = Shearing(0, 0, 0, 1, 0, 0);
			Assert::IsTrue(transform * p == Point(2, 7, 4));

			transform = Shearing(0, 0, 0, 0, 1, 0);
			Assert::IsTrue(transform * p == Point(2, 3, 6));

			transform = Shearing(0, 0, 0, 0, 0, 1);
			Assert::IsTrue(transform * p == Point(2, 3, 7));
		}

		TEST_METHOD(ChainingTransformations) {
			Tuple p = Point(1, 0, 1);
			Matrix A = RotationX(float(M_PI / 2));
			Matrix B = Scaling(5, 5, 5);
			Matrix C = Translation(10, 5, 7);
			
			Tuple p2 = A * p;
			Assert::IsTrue(p2 == Point(1, -1, 0));

			Tuple p3 = B * p2;
			Assert::IsTrue(p3 == Point(5, -5, 0));

			Tuple p4 = C * p3;
			Assert::IsTrue(p4 == Point(15, 0, 7));

			Matrix T = C * B * A;
			Assert::IsTrue(T * p == p4);
		}
	};

	TEST_CLASS(Rays) {
	public:

		TEST_METHOD(RayExists) {
			Tuple origin = Point(1, 2, 3);
			Tuple direction = Vector(4, 5, 6);
			Ray r = Ray(origin, direction);

			Assert::IsTrue(r.origin == origin);
			Assert::IsTrue(r.direction == direction);
		}

		TEST_METHOD(PositionOverTime) {
			Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));

			Assert::IsTrue(r.positionAt(0) == Point(2, 3, 4));
			Assert::IsTrue(r.positionAt(1) == Point(3, 3, 4));
			Assert::IsTrue(r.positionAt(-1) == Point(1, 3, 4));
			Assert::IsTrue(r.positionAt(2.5) == Point(4.5f, 3, 4));
		}

		TEST_METHOD(TranslatingARay) {
			Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
			Matrix m = Translation(3, 4, 5);
			Ray r2 = transform(r, m);

			Assert::IsTrue(r2.origin == Point(4, 6, 8));
			Assert::IsTrue(r2.direction == r.direction);
		}

		TEST_METHOD(ScalingARay) {
			Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
			Matrix m = Scaling(2, 3, 4);
			Ray r2 = transform(r, m);

			Assert::IsTrue(r2.origin == Point(2, 6, 12));
			Assert::IsTrue(r2.direction == Vector(0, 3, 0));
		}
	};

	TEST_CLASS(Intersections) {
	public:

		TEST_METHOD(AnIntersectionObjectExists) {
			Sphere s = Sphere();
			Intersection i = Intersection(3.5f, &s);
			Assert::AreEqual(i.t, 3.5f);
			Assert::IsTrue(*i.object == s);
		}

		TEST_METHOD(AggregatingIntersections) {
			Sphere s = Sphere();
			Intersection i1 = Intersection(1, &s);
			Intersection i2 = Intersection(2, &s);
			vector<Intersection> xs = { i1, i2 };

			Assert::AreEqual(int(xs.size()), 2);
			Assert::AreEqual(xs[0].t, 1.0f);
			Assert::AreEqual(xs[1].t, 2.0f);
		}

		TEST_METHOD(IntersectSetsObject) {
			Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s = Sphere();
			vector<Intersection> xs = intersect(&s, r);

			Assert::AreEqual(int(xs.size()), 2);
			Assert::IsTrue(*xs[0].object == s);
			Assert::IsTrue(*xs[1].object == s);
		}
	};

	TEST_CLASS(Spheres) {
	public:

		TEST_METHOD(SphereDefaultTransformation) {
			Sphere s = Sphere();
			Matrix identity = IdentityMatrix();

			Assert::IsTrue(s.transform == identity);
		}

		TEST_METHOD(ChangingSphereTransform) {
			Sphere s = Sphere();
			Matrix transform = Translation(2, 3, 4);
			s.transform = transform;

			Assert::IsTrue(s.transform == transform);
		}
	};

	TEST_CLASS(RaySphereIntersections) {
	public:
		TEST_METHOD(RayIntersectsSphereAtTwoPoints) {
			Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s = Sphere();
			vector<Intersection> xs = intersect(&s, r);

			Assert::AreEqual(int(xs.size()), 2);
			Assert::AreEqual(xs[0].t, 4.0f);
			Assert::AreEqual(xs[1].t, 6.0f);
		}

		TEST_METHOD(RayIsTangentToSphere) {
			Ray r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
			Sphere s = Sphere();
			vector<Intersection> xs = intersect(&s, r);

			Assert::AreEqual(int(xs.size()), 2);
			Assert::AreEqual(xs[0].t, xs[1].t, 5.0f);
		}

		TEST_METHOD(RayMissesASphere) {
			Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
			Sphere s = Sphere();
			vector<Intersection> xs = intersect(&s, r);

			Assert::AreEqual(int(xs.size()), 0);
		}

		TEST_METHOD(RayOriginatesInsideSphere) {
			Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
			Sphere s = Sphere();
			vector<Intersection> xs = intersect(&s, r);

			Assert::AreEqual(int(xs.size()), 2);
			Assert::AreEqual(xs[0].t, -1.0f);
			Assert::AreEqual(xs[1].t, 1.0f);
		}

		TEST_METHOD(ASphereIsBehindARay) {
			Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
			Sphere s = Sphere();
			vector<Intersection> xs = intersect(&s, r);

			Assert::AreEqual(int(xs.size()), 2);
			Assert::AreEqual(xs[0].t, -6.0f);
			Assert::AreEqual(xs[1].t, -4.0f);
		}

		TEST_METHOD(ScaledSphereAndRay) {
			Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s = Sphere();

			s.transform = Scaling(2, 2, 2);
			vector<Intersection> xs = intersect(&s, r);
			Assert::AreEqual(int(xs.size()), 2);
			Assert::AreEqual(xs[0].t, 3.0f);
			Assert::AreEqual(xs[1].t, 7.0f);
		}

		TEST_METHOD(TranslatedSphereAndRay) {
			Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
			Sphere s = Sphere();

			s.transform = Translation(5, 0, 0);
			vector<Intersection> xs = intersect(&s, r);
			Assert::AreEqual(int(xs.size()), 0);
		}
	};

	TEST_CLASS(Hits) {
	public:

		TEST_METHOD(HitWhenAllIntersectionsArePositive) {
			//A hit returns the intersection with the lower t value
			Sphere s = Sphere();
			Intersection i1 = Intersection(1, &s);
			Intersection i2 = Intersection(2, &s);
			vector<Intersection> xs = { i1, i2 };
			Intersection i = hit(xs);

			Assert::IsTrue(i == i1);
		}

		TEST_METHOD(HitWhenSomeIntersectsAreNegative) {
			//A hit returns the intersection with the lowest, non-negative t value
			Sphere s = Sphere();
			Intersection i1 = Intersection(-1, &s);
			Intersection i2 = Intersection(1, &s);
			vector<Intersection> xs = { i1, i2 };
			Intersection i = hit(xs);

			Assert::IsTrue(i == i2);
		}

		TEST_METHOD(HitWhenAllIntersectsAreNegative) {
			//A hit returns null when all intersects are negative
			Sphere s = Sphere();
			Intersection i1 = Intersection(-1, &s);
			Intersection i2 = Intersection(-2, &s);
			vector<Intersection> xs = { i1, i2 };
			Intersection i = hit(xs);

			Assert::IsTrue(i == NULL);
		}

		TEST_METHOD(HitSortsT) {
			//A hit is always the lowest nonnegative intersection
			Sphere s = Sphere();
			Intersection i1 = Intersection(5, &s);
			Intersection i2 = Intersection(7, &s);
			Intersection i3 = Intersection(-3, &s);
			Intersection i4 = Intersection(2, &s);
			vector<Intersection> xs = { i1, i2, i3, i4 };
			Intersection i = hit(xs);

			Assert::IsTrue(i == i4);
		}
	};
}
