#include "pch.h"
#include "CppUnitTest.h"
#include "../KPO_Lab2 (1).cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string arr[5] = { "1111", "1001", "1101", "1011", "1000" };
			string arrr[5] = { "1000","1001","1011","1101","1111" };
			BubleSort(arr);
			Assert::IsTrue(arr[0] == arrr[0]);
			Assert::IsTrue(arr[1] == arrr[1]);
			Assert::IsTrue(arr[2] == arrr[2]);
			Assert::IsTrue(arr[3] == arrr[3]);
			Assert::IsTrue(arr[4] == arrr[4]);
		}

		TEST_METHOD(TestMethod2) {
			string arr[5] = { "1111111","10001000","1101111","110111","10000000" };
			string arrr[5] = { "110111","1101111","1111111","10000000","10001000" };
			BubleSort(arr);
			Assert::IsTrue(arr[0] == arrr[0]);
			Assert::IsTrue(arr[1] == arrr[1]);
			Assert::IsTrue(arr[2] == arrr[2]);
			Assert::IsTrue(arr[3] == arrr[3]);
			Assert::IsTrue(arr[4] == arrr[4]);
		}
		TEST_METHOD(TestMethod3) {
			string arr[5] = { "10","1","11","110","100" };
			string arrr[5] = { "1","10","11","100","110" };
			BubleSort(arr);
			Assert::IsTrue(arr[0] == arrr[0]);
			Assert::IsTrue(arr[1] == arrr[1]);
			Assert::IsTrue(arr[2] == arrr[2]);
			Assert::IsTrue(arr[3] == arrr[3]);
			Assert::IsTrue(arr[4] == arrr[4]);
		}
		TEST_METHOD(TestMethod4) {
			string arr[5] = { "100100","100101","11", "1", "100" };
			string arrr[5] = { "1","11","100","100100","100101" };
			BubleSort(arr);
			Assert::IsTrue(arr[0] == arrr[0]);
			Assert::IsTrue(arr[1] == arrr[1]);
			Assert::IsTrue(arr[2] == arrr[2]);
			Assert::IsTrue(arr[3] == arrr[3]);
			Assert::IsTrue(arr[4] == arrr[4]);
		}
		TEST_METHOD(TestMethod5) {
			string arr[5] = { "111","1000","101","100","10" };
			string arrr[5] = { "10","100","101","111","1000" };
			BubleSort(arr);
			Assert::IsTrue(arr[0] == arrr[0]);
			Assert::IsTrue(arr[1] == arrr[1]);
			Assert::IsTrue(arr[2] == arrr[2]);
			Assert::IsTrue(arr[3] == arrr[3]);
			Assert::IsTrue(arr[4] == arrr[4]);
		}
	};
}
