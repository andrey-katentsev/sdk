#include "gtest/gtest.h"

#include "../KAA/include/format_string.h"

TEST(format_UTF8_string, d)
{
	EXPECT_EQ(u8"ќтрезок: [-1, 1].", KAA::format_string(u8"ќтрезок: [%d, %d].", -1, 1));
}

TEST(format_UTF8_string, i)
{
	EXPECT_EQ(u8"»нтервал: (-1, 1).", KAA::format_string(u8"»нтервал: (%i, %i).", -1, 1));
}

TEST(format_UTF8_string, u)
{
	EXPECT_EQ(u8"ѕоследовательность: 0, 1, 2.", KAA::format_string(u8"ѕоследовательность: %u, %u, %u.", 0, 1, 2));
}

TEST(format_UTF8_string, S)
{
	//EXPECT_EQ(u8"язык: –усский", KAA::format_string(u8"язык: %S", u8"–усский"));
	EXPECT_EQ(u8"язык: English", KAA::format_string(u8"язык: %S", u8"English"));
	//EXPECT_EQ(u8"Language: –усский", KAA::format_string(u8"Language: %S", u8"–усский"));
	EXPECT_EQ(u8"Language: English", KAA::format_string(u8"Language: %S", u8"English"));
}

TEST(format_UTF8_string, s)
{
	//EXPECT_EQ(u8"язык: –усский", KAA::format_string(u8"язык: %s", L"–усский"));
	EXPECT_EQ(u8"язык: English", KAA::format_string(u8"язык: %s", L"English"));
	//EXPECT_EQ(u8"Language: –усский", KAA::format_string(u8"Language: %s", L"–усский"));
	EXPECT_EQ(u8"Language: English", KAA::format_string(u8"Language: %s", L"English"));
}

TEST(format_UTF16_string, d)
{
	EXPECT_EQ(L"ќтрезок: [-1, 1].", KAA::format_string(L"ќтрезок: [%d, %d].", -1, 1));
}

TEST(format_UTF16_string, i)
{
	EXPECT_EQ(L"»нтервал: (-1, 1).", KAA::format_string(L"»нтервал: (%i, %i).", -1, 1));
}

TEST(format_UTF16_string, u)
{
	EXPECT_EQ(L"ѕоследовательность: 0, 1, 2.", KAA::format_string(L"ѕоследовательность: %u, %u, %u.", 0, 1, 2));
}

TEST(format_UTF16_string, S)
{
	//EXPECT_EQ(L"язык: –усский", KAA::format_string(L"язык: %S", u8"–усский"));
	EXPECT_EQ(L"язык: English", KAA::format_string(L"язык: %S", u8"English"));
	//EXPECT_EQ(L"Language: –усский", KAA::format_string(L"Language: %S", u8"–усский"));
	EXPECT_EQ(L"Language: English", KAA::format_string(L"Language: %S", u8"English"));
}

TEST(format_UTF16_string, s)
{
	EXPECT_EQ(L"язык: –усский", KAA::format_string(L"язык: %s", L"–усский"));
	EXPECT_EQ(L"язык: English", KAA::format_string(L"язык: %s", L"English"));
	EXPECT_EQ(L"Language: –усский", KAA::format_string(L"Language: %s", L"–усский"));
	EXPECT_EQ(L"Language: English", KAA::format_string(L"Language: %s", L"English"));
}
