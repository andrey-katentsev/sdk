#include "gtest/gtest.h"

#include "../KAA/include/random.h"
#include "../KAA/include/exception/operation_failure.h"

using namespace KAA::cryptography;

TEST(random, produces_different_values)
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

TEST(generate, with_invalid_arguments)
{
	auto data = 0U;
	EXPECT_EQ(0U, generate(0, &data));
	EXPECT_EQ(0U, data);
	EXPECT_TRUE(generate(0).empty());

	EXPECT_THROW(generate(0, nullptr), KAA::operation_failure);
	EXPECT_THROW(generate(1, nullptr), KAA::operation_failure);
}

class generate_vector : public testing::TestWithParam<size_t>
{};

TEST_P(generate_vector, produces_different_vectors)
{
	EXPECT_NE(generate(GetParam()), generate(GetParam()));
}

TEST_P(generate_vector, does_not_skip_boundary_bytes)
{
	const auto data = generate(GetParam());
	EXPECT_NE(0, data.front());
	EXPECT_NE(0, data.back());
}

INSTANTIATE_TEST_CASE_P(bytes_to_generate, generate_vector, testing::Values(1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U));
