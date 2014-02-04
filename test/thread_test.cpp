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
										ick::FunctionBind(Func1, &x, 100));
	
	th1->Start();
	th1->Join();
	EXPECT_EQ(5050, x);
	
	ICK_DELETE(th1);
}

