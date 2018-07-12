#include "gtest/gtest.h"

#include "../KAA/include/random.h"

using namespace KAA::cryptography;

TEST(random, random)
{
	const auto A = random();
	const auto B = random();
	const auto C = random();
	const auto D = random();
	const auto E = random();
	EXPECT_NE(A, B);
	EXPECT_NE(A, C);
	EXPECT_NE(A, D);
	EXPECT_NE(A, E);
	EXPECT_NE(B, C);
	EXPECT_NE(B, D);
	EXPECT_NE(B, E);
	EXPECT_NE(C, D);
	EXPECT_NE(C, E);
	EXPECT_NE(D, E);
}

TEST(random, generate)
{
	EXPECT_EQ(generate(0), generate(0));
	EXPECT_NE(generate(1), generate(1));
	EXPECT_NE(generate(2), generate(2));
	EXPECT_NE(generate(3), generate(3));
	EXPECT_NE(generate(4), generate(4));
	EXPECT_NE(generate(5), generate(5));
	EXPECT_NE(generate(6), generate(6));
	EXPECT_NE(generate(7), generate(7));
	EXPECT_NE(generate(8), generate(8));
}
