#include "test_base.h"

class FunctionTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

static int f1(int x){
	return x * 2;
}

static void f2(){
	
}

static int f3(int x){
	return x * 2;
}

TEST_F(FunctionTest, function_thread){
	ick::Function<int (*)(int)> g1 = f1;
	ick::Function<int (*)()> g2 = ick::FunctionBind1(g1, 2);
	ick::Function<int (*)()> g3 = ick::FunctionBind1(f1, 2);
	
	EXPECT_EQ(2, g1(1));
	EXPECT_EQ(4, g2());
	EXPECT_EQ(6, g3());

}