#include "pch.h"
#include "CppUnitTest.h"
#include "..\KPO_Lab2 (4).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int arr[8] = { 1,2,3,4,5,6,7,8 };
			bool test;
			test = Test(arr);
			Assert::IsFalse(test);
		}
		TEST_METHOD(TestMethod2)
		{
			int arr[8] = { 1,2,3,4,5,6,7,10000 };
			bool test;
			test = Test(arr);
			Assert::IsFalse(test);
		}
		TEST_METHOD(TestMethod3)
		{
			int arr[8] = { 1,2,2,2,2,2,2,2 };
			bool test;
			test = Test(arr);
			Assert::IsTrue(test);
		}
		TEST_METHOD(TestMethod4)
		{
			int arr[8] = { 1,10,2,25,2,3,2,2 };
			bool test;
			test = Test(arr);
			Assert::IsFalse(test);
		}
		TEST_METHOD(TestMethod5)
		{
			int arr[8] = { 1,1,1,1,1,1,1,1 };
			bool test;
			test = Test(arr);
			Assert::IsTrue(test);
		}

	};
}
