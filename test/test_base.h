#pragma once

#include <gtest/gtest.h>
#include <ick/ick.h>

class TestBase : public testing::Test {
protected:
	virtual void SetUp(){
		struct ick::StartupInfo info = { NULL, true };
		ick::Startup(info);
	}
	virtual void TearDown(){

		EXPECT_EQ(0, ick::g_)
		ick::Shutdown();
	}
};
