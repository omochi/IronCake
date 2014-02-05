#include "test_base.h"

class TaskQueueThreadTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

//LoopThreadではロックがいらない
void f1(int * x, bool cancelled){
	(void)cancelled;
	int ox = *x;
	*x = *x + 1;
	EXPECT_EQ(ox + 1, *x);
}

void f1_post(ick::TaskQueueThread * lp, int * x, int n){
	for(int i=0;i<n;i++){
		lp->Post(ICK_NEW(ick::Task, ick::FunctionBind(f1, x)));
		ick::Sleep(0.001);
	}
}

TEST_F(TaskQueueThreadTest, test1){
	ick::TaskQueueThread * task_thread = ICK_NEW(ick::TaskQueueThread);
	task_thread->Start();
	
	ick::Array<ick::Thread *> ps(16);
	int x = 0;
	
	//インクリメントを1つのスレッドから10個投げ込む
	for (int i = 0; i < ps.num(); i++){
		ps[i] = ICK_NEW(ick::FunctionThread, ick::FunctionBind(f1_post, task_thread, &x, 10));
		ps[i]->Start();
	}
	
	for (int i = 0; i < ps.num(); i++){
		ps[i]->Join();
		ICK_DELETE(ps[i]);
	}
	
	task_thread->PostQuit();
	task_thread->Join();
	ICK_DELETE(task_thread);
	
	EXPECT_EQ(ps.num() * 10, x);

}
