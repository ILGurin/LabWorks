#include "pch.h"
#include "CppUnitTest.h"
#include "..\KPO_Lab2 (2.1).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::IsTrue(Fib(5) == 3);
			Assert::IsTrue(Fib(10) == 34);
			Assert::IsTrue(Fib(20) == 4181);
			Assert::IsTrue(Fib(15) == 377);
			Assert::IsTrue(Fib(9) == 21);
		}
	};
}
