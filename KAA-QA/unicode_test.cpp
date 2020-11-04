#include "gtest/gtest.h"

#include "../KAA/include/unicode.h"

using namespace KAA::unicode;

TEST(UTF16_to_UTF8, ru_RU)
{
	const auto UTF16 = std::wstring { L"Русский" };
	const auto UTF8 = to_UTF8(UTF16);
	EXPECT_TRUE(UTF16 == to_UTF16(UTF8));
}

TEST(UTF16_to_UTF8, en_US)
{
	const auto UTF16 = std::wstring { L"English" };
	const auto UTF8 = to_UTF8(UTF16);
	EXPECT_TRUE(UTF16 == to_UTF16(UTF8));
}
