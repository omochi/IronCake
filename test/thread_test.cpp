#include "test_base.h"

class ThreadTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

class Thread1 : public ick::Thread {
public:
	int x;
	int n;
	virtual void Run(){
		x = 0;
		for(int i = 1; i <= n; i++){
			x += i;
		}
	}
};

TEST_F(ThreadTest, extends_thread){
	Thread1 * th1 = ICK_NEW(Thread1);
	th1->n = 100;
	th1->Start();
	th1->Join();
	EXPECT_EQ(5050, th1->x);
	ICK_DELETE(th1);
}

void Func1(int * x, int n){
	int xt = 0;
	for(int i = 1; i <= n; i++){ xt+=i; }
	*x = xt;
}

TEST_F(ThreadTest, function_thread){
	int x;
	ick::FunctionThread * th1 = ICK_NEW(ick::FunctionThread,
										ick::FunctionBind2(Func1, &x, 100));
	
	th1->Start();
	th1->Join();
	EXPECT_EQ(5050, x);
	
	ICK_DELETE(th1);
}

void f2(ick::Mutex * mutex,int * x){
	mutex->Lock();
	EXPECT_EQ(0, *x);
	*x = *x + 1;
	usleep(10*1000);
	EXPECT_EQ(1, *x);
	*x = *x - 1;
	EXPECT_EQ(0, *x);
	mutex->Unlock();
}

TEST_F(ThreadTest, mutex){
	ick::Array<ick::Thread *> ths(16);
	ick::Mutex mutex;
	int x = 0;
	for(int i = 0; i < ths.num(); i++){
		ths[i] = ICK_NEW(ick::FunctionThread, ick::FunctionBind2(f2, &mutex, &x));
		ths[i]->Start();
	}
	for(int i = 0; i < ths.num(); i++){
		ths[i]->Join();
		ICK_DELETE(ths[i]);
	}
}
