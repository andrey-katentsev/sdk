#include "gtest/gtest.h"

#include "../KAA/include/format_string.h"

TEST(format_UTF8_string, d)
{
	EXPECT_EQ(u8"�������: [-1, 1].", KAA::format_string(u8"�������: [%d, %d].", -1, 1));
}

TEST(format_UTF8_string, i)
{
	EXPECT_EQ(u8"��������: (-1, 1).", KAA::format_string(u8"��������: (%i, %i).", -1, 1));
}

TEST(format_UTF8_string, u)
{
	EXPECT_EQ(u8"������������������: 0, 1, 2.", KAA::format_string(u8"������������������: %u, %u, %u.", 0, 1, 2));
}

TEST(format_UTF8_string, S)
{
	//EXPECT_EQ(u8"����: �������", KAA::format_string(u8"����: %S", u8"�������"));
	EXPECT_EQ(u8"����: English", KAA::format_string(u8"����: %S", u8"English"));
	//EXPECT_EQ(u8"Language: �������", KAA::format_string(u8"Language: %S", u8"�������"));
	EXPECT_EQ(u8"Language: English", KAA::format_string(u8"Language: %S", u8"English"));
}

TEST(format_UTF8_string, s)
{
	//EXPECT_EQ(u8"����: �������", KAA::format_string(u8"����: %s", L"�������"));
	EXPECT_EQ(u8"����: English", KAA::format_string(u8"����: %s", L"English"));
	//EXPECT_EQ(u8"Language: �������", KAA::format_string(u8"Language: %s", L"�������"));
	EXPECT_EQ(u8"Language: English", KAA::format_string(u8"Language: %s", L"English"));
}

TEST(format_UTF16_string, d)
{
	EXPECT_EQ(L"�������: [-1, 1].", KAA::format_string(L"�������: [%d, %d].", -1, 1));
}

TEST(format_UTF16_string, i)
{
	EXPECT_EQ(L"��������: (-1, 1).", KAA::format_string(L"��������: (%i, %i).", -1, 1));
}

TEST(format_UTF16_string, u)
{
	EXPECT_EQ(L"������������������: 0, 1, 2.", KAA::format_string(L"������������������: %u, %u, %u.", 0, 1, 2));
}

TEST(format_UTF16_string, S)
{
	//EXPECT_EQ(L"����: �������", KAA::format_string(L"����: %S", u8"�������"));
	EXPECT_EQ(L"����: English", KAA::format_string(L"����: %S", u8"English"));
	//EXPECT_EQ(L"Language: �������", KAA::format_string(L"Language: %S", u8"�������"));
	EXPECT_EQ(L"Language: English", KAA::format_string(L"Language: %S", u8"English"));
}

TEST(format_UTF16_string, s)
{
	EXPECT_EQ(L"����: �������", KAA::format_string(L"����: %s", L"�������"));
	EXPECT_EQ(L"����: English", KAA::format_string(L"����: %s", L"English"));
	EXPECT_EQ(L"Language: �������", KAA::format_string(L"Language: %s", L"�������"));
	EXPECT_EQ(L"Language: English", KAA::format_string(L"Language: %s", L"English"));
}
