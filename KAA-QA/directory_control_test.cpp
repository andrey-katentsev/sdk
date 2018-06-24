#include "gtest/gtest.h"

#include "../KAA/include/filesystem/crt_directory_control.h"

#include <memory>

namespace
{
	// FUTURE: KAA: replace working_directory_session with SetUp()/TearDown().
	class working_directory_session
	{
	public:
		explicit working_directory_session(const std::wstring& path) : previous_working_directory(environment.get_current_working_directory())
		{
			environment.set_current_working_directory(path);
		}

		~working_directory_session()
		{
			environment.set_current_working_directory(previous_working_directory);
		}

	private:
		KAA::filesystem::crt_directory_control environment;
		const std::wstring previous_working_directory;
	};
}

using namespace KAA::filesystem;

TEST(current_working_directory, get)
{
	// ARRANGE
	const auto environment = std::make_unique<crt_directory_control>();
	// ACT
	const auto current_working_directory = environment->get_current_working_directory();
	// ASSERT
	ASSERT_FALSE(current_working_directory.empty());
}

TEST(current_working_directory, set)
{
	// ARRANGE
	const auto environment = std::make_unique<crt_directory_control>();
	const auto current_working_directory = environment->get_current_working_directory();
	const auto new_working_directory = std::wstring { LR"(C:\Temp)" }; // FIX: KAA: must exists!

	// ACT
	const working_directory_session session { new_working_directory };

	// ASSERT
	ASSERT_EQ(new_working_directory, environment->get_current_working_directory());
}

TEST(working_directory_session, sets_and_restores_current_working_directory)
{
	// ARRANGE
	const auto environment = std::make_unique<crt_directory_control>();
	const auto current_working_directory = environment->get_current_working_directory();

	// ACT
	{
		const auto new_working_directory = std::wstring { LR"(C:\Temp)" }; // FIX: KAA: must exists!
		const working_directory_session session { new_working_directory };
		EXPECT_EQ(new_working_directory, environment->get_current_working_directory());
	}

	// ASSERT
	ASSERT_EQ(current_working_directory, environment->get_current_working_directory());
}
