#include "pch.h"
#include "CppUnitTest.h"
#include "..\KPO_Lab2 (3).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::IsTrue(2008 == Sum50());
		}
	};
}
