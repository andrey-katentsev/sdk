#include "gtest/gtest.h"

#include "../KAA/include/unicode.h"

using namespace KAA::unicode;

TEST(to_UTF16, ru_RU)
{
	EXPECT_TRUE(L"Русский" == to_UTF16(u8"Русский"));
}

TEST(to_UTF16, en_US)
{
	EXPECT_TRUE(L"English" == to_UTF16(u8"English"));
}

TEST(to_UTF8, ru_RU)
{
	EXPECT_TRUE(u8"Русский" == to_UTF8(L"Русский"));
}

TEST(to_UTF8, en_US)
{
	EXPECT_TRUE(u8"English" == to_UTF8(L"English"));
}

TEST(UTF8_to_UTF16, ru_RU)
{
	const auto UTF8 = std::string { u8"Русский" };
	EXPECT_TRUE(UTF8 == to_UTF8(to_UTF16(UTF8)));
}

TEST(UTF8_to_UTF16, en_US)
{
	const auto UTF8 = std::string { u8"English" };
	EXPECT_TRUE(UTF8 == to_UTF8(to_UTF16(UTF8)));
}

TEST(UTF16_to_UTF8, ru_RU)
{
	const auto UTF16 = std::wstring { L"Русский" };
	EXPECT_TRUE(UTF16 == to_UTF16(to_UTF8(UTF16)));
}

TEST(UTF16_to_UTF8, en_US)
{
	const auto UTF16 = std::wstring { L"English" };
	EXPECT_TRUE(UTF16 == to_UTF16(to_UTF8(UTF16)));
}
