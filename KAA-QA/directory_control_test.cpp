#include "gtest/gtest.h"

#include "../KAA/include/filesystem/crt_directory_control.h"

#include <memory>

namespace
{
	/*const std::wstring kibibyte(L"./bin/KiB.bin");

	/*const KAA::filesystem::driver::mode read_attributes_only(false, false);
	const KAA::filesystem::driver::mode sequential_binary_read_only(false, true);
	const KAA::filesystem::driver::mode sequential_binary_write_only(true, false);
	const KAA::filesystem::driver::mode sequential_binary_read_write(true, true);

	const KAA::filesystem::driver::share share_any_access;*/

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

TEST(current_working_directory, set)
{
	const auto environment = std::make_unique<crt_directory_control>();
	const auto current_working_directory = environment->get_current_working_directory();
	const auto new_working_directory = std::wstring { LR"(C:\Temp)" }; // FIX: KAA: must exists!

	const working_directory_session session { new_working_directory };

	//environment->set_current_working_directory(new_working_directory); // FIX: KAA: auto restore!
	EXPECT_EQ(new_working_directory, environment->get_current_working_directory());
}
