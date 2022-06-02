#include "pch.h"
#include "CppUnitTest.h"
#include "..\Lab12_6.9\main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Node* root = nullptr;
			root = Insert(root, 2);
			Assert::AreEqual(root->info, 2);
		}
	};
}
