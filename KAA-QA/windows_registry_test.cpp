#include "gtest/gtest.h"

#include "../KAA/include/windows_registry.h"
#include "../KAA/include/windows_registry_key.h"
#include "../KAA/include/exception/windows_api_failure.h"

using namespace KAA::system;

namespace
{
	constexpr windows_registry::key_access set_value_only { false, false, false, false, false, true };
	constexpr windows_registry::key_access query_value_only { false, false, false, false, true, false };
}

TEST(query_string_value, data_exists)
{
	windows_registry registry;
	auto key = registry.open_key(windows_registry::current_user, R"(Software\KAA)", query_value_only);
	const auto data = key->query_string_value("name");
	EXPECT_TRUE(u8"������" == data);
}

TEST(query_dword_value, data_exists)
{
	windows_registry registry;
	auto key = registry.open_key(windows_registry::current_user, R"(Software\KAA)", query_value_only);
	const auto data = key->query_dword_value("age");
	EXPECT_EQ(34U, data);
}

TEST(query_string_value, data_not_exists)
{
	windows_registry registry;
	auto key = registry.open_key(windows_registry::current_user, R"(Software\KAA)", query_value_only);
	EXPECT_THROW(key->query_string_value("<none>"), KAA::windows_api_failure);
}

TEST(query_dword_value, data_not_exists)
{
	windows_registry registry;
	auto key = registry.open_key(windows_registry::current_user, R"(Software\KAA)", query_value_only);
	EXPECT_THROW(key->query_dword_value("<none>"), KAA::windows_api_failure);
}

TEST(set_string_value, data_not_exists)
{
	windows_registry registry;
	auto key = registry.open_key(windows_registry::current_user, R"(Software\KAA)", set_value_only);
	EXPECT_NO_THROW(key->set_string_value("email", "hyperlink@inbox.ru"));
}

TEST(set_dword_value, data_not_exists)
{
	windows_registry registry;
	auto key = registry.open_key(windows_registry::current_user, R"(Software\KAA)", set_value_only);
	EXPECT_NO_THROW(key->set_dword_value("year", 2020));
}
