#include "pch.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include "../Tuple.cpp"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace RayTracerTests {

	TEST_CLASS(Tuples) {

	public:
		TEST_METHOD(ATupleIsAPoint) {
			//A tuple with w = 1.0 is a point
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
			//A tuple with w = 0 is a vector
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
			Tuple* a = point(4, -4, 3);
			Tuple b = Tuple(4, -4, 3, 1);
			Assert::AreEqual(a->x, b.x);
			Assert::AreEqual(a->y, b.y);
			Assert::AreEqual(a->z, b.z);
			Assert::AreEqual(a->w, b.w);
		}

		TEST_METHOD(AVectorIsAVector) {
			Tuple* a = vector(4, -4, 3);
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
			//A point minus a point is a vector
			Tuple* a = point(3, 2, 1);
			Tuple* b = point(5, 6, 7);
			Tuple* c = vector(-2, -4, -6);
			Assert::IsTrue((*a - *b) == *c);
		}

		TEST_METHOD(PointVectorSubtraction) {
			//A point minus a vector is a point
			Tuple* a = point(3, 2, 1);
			Tuple* b = vector(5, 6, 7);
			Tuple* c = point(-2, -4, -6);
			Assert::IsTrue((*a - *b) == *c);
		}

		TEST_METHOD(VectorSubtraction) {
			//A vector minus a vector is a vector
			Tuple* a = vector(3, 2, 1);
			Tuple* b = vector(5, 6, 7);
			Tuple* c = vector(-2, -4, -6);
			Assert::IsTrue((*a - *b) == *c);
		}

		TEST_METHOD(SubtractingFromZeroVector) {
			Tuple* zero = vector(0, 0, 0);
			Tuple* v = vector(1, -2, 3);
			Tuple* vNegation = vector(-1, 2, -3);
			Assert::IsTrue((*zero - *v) == *vNegation);
		}

		TEST_METHOD(TupleNegation) {
			//A tuple subtracted from the zero vector is negated
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
			Tuple* v1 = vector(1, 0, 0);
			float m = v1->magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple* v2 = vector(0, 1, 0);
			m = v2->magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple* v3 = vector(0, 0, 1);
			m = v3->magnitude();
			Assert::AreEqual(m, 1.0f);

			Tuple* v4 = vector(1, 2, 3);
			m = v4->magnitude();
			Assert::AreEqual(m, float(sqrt(14)));

			Tuple* v5 = vector(-1, -2, -3);
			m = v5->magnitude();
			Assert::AreEqual(m, float(sqrt(14)));
		}

		TEST_METHOD(NormalizingAVector) {
			Tuple* v = vector(4, 0, 0);
			Tuple* nv = normalize(v);
			Tuple* uv = vector(1, 0, 0);
			Assert::IsTrue(*nv == *uv);

			v = vector(1, 2, 3);
			nv = normalize(v);
			uv = vector(1 / float(sqrt(14)), 2 / float(sqrt(14)), 3 / float(sqrt(14)));
			Assert::IsTrue(*nv == *uv);
		}

		TEST_METHOD(MagnitudeOfNormalizedVector) {
			Tuple* v = vector(1, 2, 3);
			Tuple* nv = normalize(v);
			Assert::IsTrue(equal(nv->magnitude(), 1.0f));
		}

		TEST_METHOD(DotProductOfTwoTuples) {
			Tuple* a = vector(1, 2, 3);
			Tuple* b = vector(2, 3, 4);
			Assert::AreEqual(dot(a, b), 20);
		}
	};
}
