#include "gtest/gtest.h"

#include "../KAA/include/critical_section.h"

using namespace KAA::synchronization;

TEST(critical_section, debug)
{
	{
		critical_section sync;
		EXPECT_NO_THROW(sync.seize());
		EXPECT_NO_THROW(sync.release());
	}
	{
		critical_section sync { 1000 };
		EXPECT_NO_THROW(sync.seize());
		EXPECT_NO_THROW(sync.release());
	}
	{
		critical_section sync { 1000, true };
		EXPECT_NO_THROW(sync.seize());
		EXPECT_NO_THROW(sync.release());
	}
}
