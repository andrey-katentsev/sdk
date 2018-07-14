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

TEST(cryptography, protect_data)
{
	// {1EBCA742-1651-4559-B6BE-D4A20650895D}
	// constexpr GUID test_id = { 0x1ebca742, 0x1651, 0x4559, { 0xb6, 0xbe, 0xd4, 0xa2, 0x6, 0x50, 0x89, 0x5d } };
	const std::vector<uint8_t> data = { 0xb6, 0xbe, 0xd4, 0xa2, 0x6, 0x50, 0x89, 0x5d };
	const auto encrypted_data = KAA::cryptography::protect_data(&data[0], data.size());
	EXPECT_NE(data, encrypted_data);
	const auto decrypted_data = KAA::cryptography::unprotect_data(&encrypted_data[0], encrypted_data.size());
	EXPECT_EQ(data, decrypted_data);
}
