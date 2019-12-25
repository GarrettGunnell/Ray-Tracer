#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace RayTracerTests {

	TEST_CLASS(RayTracerTests) {

	public:
		
		TEST_METHOD(ATupleIsAPoint) {
			//A tuple with w = 1.0 is a point
			Tuple a = tuple(4.3, -4.2, 3.1, 1.0);
			Assert::AreEqual(4.3, a.x);
			Assert::AreEqual(-4.2, a.y);
			Assert::AreEqual(3.1, a.z);
			Assert::AreEqual(1.0, a.w);
			Assert::IsTrue(a.isPoint());
			Assert::IsFalse(a.isVector());
		}

		TEST_METHOD(ATupleIsAVector) {
			//A tuple with w = 0 is a vector
			Tuple a = tuple(4.3, -4.2, 3.1, 0.0);
			Assert::AreEqual(4.3, a.x);
			Assert::AreEqual(-4.2, a.y);
			Assert::AreEqual(3.1, a.z);
			Assert::AreEqual(0.0, a.w);
			Assert::IsFalse(a.isPoint());
			Assert::IsTrue(a.isVector());
		}
	};
}
