#include "test_base.h"

class LoopThreadTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

//LoopThreadではロックがいらない
void f1(int * x){
	int ox = *x;
	*x = *x + 1;
	ick::Sleep(0.001);
	EXPECT_EQ(ox + 1, *x);
}

void f1_post(ick::LoopThread * lp, int * x, int n){
	for(int i=0;i<n;i++){
		lp->Post(ick::FunctionBind1(f1, x));
		ick::Sleep(0.001);
	}
}

TEST_F(LoopThreadTest, test1){
	ick::LoopThread * loop_thread = ICK_NEW(ick::LoopThread);
	loop_thread->Start();
	
	ick::Array<ick::Thread *> ps(16);
	int x = 0;
	
	//インクリメントを1つのスレッドから10個投げ込む
	for (int i = 0; i < ps.num(); i++){
		ps[i] = ICK_NEW(ick::FunctionThread, ick::FunctionBind3(f1_post, loop_thread, &x, 10));
		ps[i]->Start();
	}
	
	for (int i = 0; i < ps.num(); i++){
		ps[i]->Join();
		ICK_DELETE(ps[i]);
	}
	
	loop_thread->PostQuit();
	loop_thread->Join();
	ICK_DELETE(loop_thread);
	
	EXPECT_EQ(ps.num() * 10, x);

}
