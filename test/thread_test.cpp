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

void Func1(int n, int * x){
	int xt = 0;
	for(int i = 1; i <= n; i++){ xt+=i; }
	*x = xt;
}

int f1(int x){
	return x * 2;
}

void f2(){
	
}

int f3(int x){
	return x * 2;
}

TEST_F(ThreadTest, function_thread){
	ick::Function<int (*)(int)> g1 = f1;
	ick::Function<int (*)()> g2 = ick::FunctionBind1(g1, 2);
	ick::Function<int (*)()> g3 = ick::FunctionBind1(f1, 2);
	
	EXPECT_EQ(2, g1(1));
	EXPECT_EQ(4, g2());
	EXPECT_EQ(6, g3());


//	
//	
//	struct Func1Closure {
//		int x;
//		int n;
//		void operator() (void) {
//			Func1(n,&x);
//		};
//	} func1Closure;
//	func1Closure.n = 100;
//	ick::FunctionThread<Func1Closure> * th1 = ICK_NEW1(ick::FunctionThread<Func1Closure>, func1Closure);
//	th1->Start();
//	th1->Join();
//	EXPECT_EQ(5050, th1->function().x);
//	ICK_DELETE(th1);
}
