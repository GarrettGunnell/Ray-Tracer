#include "pch.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include "../Tuple.cpp"
#include "../Color.cpp"
#include "../Canvas.cpp"
#include "../Matrix.cpp"

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
			Tuple* a = Point(4, -4, 3);
			Tuple b = Tuple(4, -4, 3, 1);
			Assert::AreEqual(a->x, b.x);
			Assert::AreEqual(a->y, b.y);
			Assert::AreEqual(a->z, b.z);
			Assert::AreEqual(a->w, b.w);
		}

		TEST_METHOD(AVectorIsAVector) {
			Tuple* a = Vector(4, -4, 3);
			Tuple b = Tuple(4, -4, 3, 0);
			Assert::AreEqual(a->x, b.x);
			Assert::AreEqual(a->y, b.y);
			Assert::AreEqual(a->z, b.z);
			Assert::AreEqual(a->w, b.w);
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
			Tuple* a = Point(3, 2, 1);
			Tuple* b = Point(5, 6, 7);
			Tuple* c = Vector(-2, -4, -6);
			Assert::IsTrue((*a - *b) == *c);
		}

		TEST_METHOD(PointVectorSubtraction) {
			//A Point minus a Vector is a Point
			Tuple* a = Point(3, 2, 1);
			Tuple* b = Vector(5, 6, 7);
			Tuple* c = Point(-2, -4, -6);
			Assert::IsTrue((*a - *b) == *c);
		}

		TEST_METHOD(VectorSubtraction) {
			//A Vector minus a Vector is a Vector
			Tuple* a = Vector(3, 2, 1);
			Tuple* b = Vector(5, 6, 7);
			Tuple* c = Vector(-2, -4, -6);
			Assert::IsTrue((*a - *b) == *c);
		}

		TEST_METHOD(SubtractingFromZeroVector) {
			Tuple* zero = Vector(0, 0, 0);
			Tuple* v = Vector(1, -2, 3);
			Tuple* vNegation = Vector(-1, 2, -3);
			Assert::IsTrue((*zero - *v) == *vNegation);
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
			Tuple* v1 = Vector(1, 0, 0);
			float m = v1->magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple* v2 = Vector(0, 1, 0);
			m = v2->magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple* v3 = Vector(0, 0, 1);
			m = v3->magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple* v4 = Vector(1, 2, 3);
			m = v4->magnitude();
			Assert::AreEqual(m, float(sqrt(14)));

			Tuple* v5 = Vector(-1, -2, -3);
			m = v5->magnitude();
			Assert::AreEqual(m, float(sqrt(14)));
		}

		TEST_METHOD(NormalizingAVector) {
			Tuple* v = Vector(4, 0, 0);
			Tuple* nv = normalize(v);
			Tuple* uv = Vector(1, 0, 0);
			Assert::IsTrue(*nv == *uv);

			v = Vector(1, 2, 3);
			nv = normalize(v);
			uv = Vector(1 / float(sqrt(14)), 2 / float(sqrt(14)), 3 / float(sqrt(14)));
			Assert::IsTrue(*nv == *uv);
		}

		TEST_METHOD(MagnitudeOfNormalizedVector) {
			Tuple* v = Vector(1, 2, 3);
			Tuple* nv = normalize(v);
			Assert::IsTrue(equal(nv->magnitude(), 1.0f));
		}

		TEST_METHOD(DotProductOfTwoTuples) {
			Tuple* a = Vector(1, 2, 3);
			Tuple* b = Vector(2, 3, 4);
			Assert::AreEqual(dot(a, b), 20.0f);
		}

		TEST_METHOD(CrossProductOfTwoVectors) {
			Tuple* a = Vector(1, 2, 3);
			Tuple* b = Vector(2, 3, 4);
			Tuple* crossab = Vector(-1, 2, -1);
			Tuple* crossba = Vector(1, -2, 1);
			Tuple* crossabf = cross(a, b);
			Tuple* crossbaf = cross(b, a);
			Assert::IsTrue(*crossabf == *crossab);
			Assert::IsTrue(*crossbaf == *crossba);
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
					c.writePixel(j, i, Color(1, 0.8, 0.6));
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

			Assert::AreEqual(A * B, C);
		}
	};
}
