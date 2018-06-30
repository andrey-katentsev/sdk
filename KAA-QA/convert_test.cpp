#include "gtest/gtest.h"

#include "../KAA/include/convert.h"
#include "../KAA/include/exception/system_failure.h"

using namespace KAA::convert;

TEST(convert, long_to_wstring)
{
	EXPECT_EQ(std::wstring(L"0"), to_wstring(0L));
	EXPECT_EQ(std::wstring(L"1"), to_wstring(1L));
	EXPECT_EQ(std::wstring(L"-1"), to_wstring(-1L));
	EXPECT_EQ(std::wstring(L"128"), to_wstring(128L));
	EXPECT_EQ(std::wstring(L"-128"), to_wstring(-128L));
}

TEST(convert, long_to_wstring_hex)
{
	enum { hex = 16 };
	EXPECT_EQ(std::wstring(L"0"), to_wstring(0L, hex));
	EXPECT_EQ(std::wstring(L"1"), to_wstring(1L, hex));
	EXPECT_EQ(std::wstring(L"ffffffff"), to_wstring(-1L, hex));
	EXPECT_EQ(std::wstring(L"80"), to_wstring(128L, hex));
	EXPECT_EQ(std::wstring(L"ffffff80"), to_wstring(-128L, hex));
}

TEST(convert, wstring_to_long)
{
	// radix (base) is between 2 and 36
	const auto any_value = std::wstring();
	EXPECT_THROW(to_long(any_value, 0), KAA::system_failure);
	EXPECT_THROW(to_long(any_value, 1), KAA::system_failure);
	EXPECT_NO_THROW(to_long(any_value, 2));
	EXPECT_NO_THROW(to_long(any_value, 36));
	EXPECT_THROW(to_long(any_value, 37), KAA::system_failure);

	EXPECT_EQ(0L, to_long(std::wstring()));
	EXPECT_EQ(0L, to_long(std::wstring(L"0")));
	EXPECT_EQ(1L, to_long(std::wstring(L"1")));
	EXPECT_EQ(-1L, to_long(std::wstring(L"-1")));
	EXPECT_EQ(128L, to_long(std::wstring(L"128")));
	EXPECT_EQ(-128L, to_long(std::wstring(L"-128")));
}

TEST(convert, wstring_to_long_hex)
{
	enum { hex = 16 };
	EXPECT_EQ(0L, to_long(std::wstring(L"0"), hex));
	EXPECT_EQ(1L, to_long(std::wstring(L"1"), hex));
	EXPECT_EQ(127L, to_long(std::wstring(L"7f"), hex));
	EXPECT_EQ(128L, to_long(std::wstring(L"80"), hex));
}

TEST(convert, ulong_to_wstring)
{
	EXPECT_EQ(std::wstring(L"0"), to_wstring(0UL));
	EXPECT_EQ(std::wstring(L"1"), to_wstring(1UL));
	EXPECT_EQ(std::wstring(L"127"), to_wstring(127UL));
	EXPECT_EQ(std::wstring(L"128"), to_wstring(128UL));
}

TEST(convert, ulong_to_wstring_hex)
{
	enum { hex = 16 };
	EXPECT_EQ(std::wstring(L"0"), to_wstring(0UL, hex));
	EXPECT_EQ(std::wstring(L"1"), to_wstring(1UL, hex));
	EXPECT_EQ(std::wstring(L"7f"), to_wstring(127UL, hex));
	EXPECT_EQ(std::wstring(L"80"), to_wstring(128UL, hex));
}

TEST(convert, wstring_to_ulong)
{
	// radix (base) is between 2 and 36
	const auto any_value = std::wstring();
	EXPECT_THROW(to_ulong(any_value, 0), KAA::system_failure);
	EXPECT_THROW(to_ulong(any_value, 1), KAA::system_failure);
	EXPECT_NO_THROW(to_ulong(any_value, 2));
	EXPECT_NO_THROW(to_ulong(any_value, 36));
	EXPECT_THROW(to_ulong(any_value, 37), KAA::system_failure);

	EXPECT_EQ(0UL, to_ulong(std::wstring()));
	EXPECT_EQ(0UL, to_ulong(std::wstring(L"0")));
	EXPECT_EQ(1UL, to_ulong(std::wstring(L"1")));
	EXPECT_EQ(127UL, to_ulong(std::wstring(L"127")));
	EXPECT_EQ(128UL, to_ulong(std::wstring(L"128")));
}

TEST(convert, wstring_to_ulong_hex)
{
	enum { hex = 16 };
	EXPECT_EQ(0UL, to_ulong(std::wstring(L"0"), hex));
	EXPECT_EQ(1UL, to_ulong(std::wstring(L"1"), hex));
	EXPECT_EQ(127UL, to_ulong(std::wstring(L"7F"), hex));
	EXPECT_EQ(128UL, to_ulong(std::wstring(L"80"), hex));
}
