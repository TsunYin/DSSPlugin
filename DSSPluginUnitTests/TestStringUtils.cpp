#include "stdafx.h"
#include "CppUnitTest.h"
#include "../DSSPlugin/StringUtils.cpp"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DSSPluginUnitTests
{
	TEST_CLASS(TestStringUtils)
	{
	public:	
		
		TEST_METHOD(test_lower_case)
		{
			std::string before = "AbCdEfG";
			std::string after = lower_case(before);

			Assert::IsFalse(before == after);
			Assert::IsTrue("abcdefg" == after);
		}

		TEST_METHOD(test_trim)
		{
			std::string before = "  asdf  ";
			std::string after = trim(before);
			Assert::IsFalse(before == after);

			Assert::IsTrue("as df" == trim("  as df"));
			Assert::IsTrue("as df" == trim("as df  "));
			Assert::IsTrue("as df" == trim("  as df  "));
			Assert::IsTrue("as df" == trim("as df"));
		}
	};


}