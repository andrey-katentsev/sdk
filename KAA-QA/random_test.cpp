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
