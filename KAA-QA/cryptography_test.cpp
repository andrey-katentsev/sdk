#include "gtest/gtest.h"

#include "../KAA/include/cryptography.h"

TEST(cryptography, gamma)
{
	constexpr int data = 0x1bca4ac8;
	constexpr int key = 0xce30ffae;

	int encrypted_data = 0;
	KAA::cryptography::gamma(&data, &key, &encrypted_data, sizeof(encrypted_data));
	EXPECT_EQ(0xd5fab566, encrypted_data);

	int decrypted_data = 0;
	KAA::cryptography::gamma(&encrypted_data, &key, &decrypted_data, sizeof(decrypted_data));
	EXPECT_EQ(data, decrypted_data);
}
