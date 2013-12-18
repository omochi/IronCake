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
	Thread1 * th1 = ICK_NEW0(Thread1);
	th1->n = 100;
	th1->Start();
	th1->Join();
	EXPECT_EQ(5050, th1->x);
	ICK_DELETE(th1);
}

void Func1(int n, int * x){
	int xt = 0;
	for(int i = 1; i <= n; i++){ xt+=i; }
	*x = xt;
}

int f1(){
	return 1;
}

void f2(){
	
}

int f3(int x){
	return x * 2;
}

TEST_F(ThreadTest, function_thread){
	
	ick::NativeFunction<int (*)()> nf1(f1);
	EXPECT_EQ(1, nf1());
	
	ick::NativeFunction<void (*)()> nf2(f2);
	nf2();
	

	
	
	struct Func1Closure {
		int x;
		int n;
		void operator() (void) {
			Func1(n,&x);
		};
	} func1Closure;
	func1Closure.n = 100;
	ick::FunctionThread<Func1Closure> * th1 = ICK_NEW1(ick::FunctionThread<Func1Closure>, func1Closure);
	th1->Start();
	th1->Join();
	EXPECT_EQ(5050, th1->function().x);
	ICK_DELETE(th1);
}
