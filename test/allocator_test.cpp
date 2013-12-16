#include <gtest/gtest.h>
#include <ick/ick.h>

class AllocatorTest : public testing::Test {
protected:
	virtual void SetUp(){
		struct ick::StartupInfo info = { NULL, false };
		ick::Startup(info);
	}
	virtual void TearDown(){
		ick::Shutdown();
	}
};

TEST_F(AllocatorTest, test1){
	ick::MallocAllocator ma;
	void * p = ma.Allocate(128, 32);
	EXPECT_TRUE(p);
	EXPECT_EQ(0x0, ((uintptr_t)p & 0x0F));
	ma.Free(p);
}
