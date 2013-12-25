#pragma once

#include <gtest/gtest.h>
#include <ick/ick.h>

class TestBase : public testing::Test {
protected:
	virtual void SetUp();
	virtual void TearDown();
};
