#include "test_base.h"

class WaitTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

class ThreadGate {
	ick::Mutex mutex_;
	bool opened_;
public:
	ThreadGate(){
		opened_ = false;
	}
	void Pass(){
		mutex_.Lock();
		while (!opened_){
			mutex_.Wait();
			if (opened_){
				break;
			}
		}
		opened_ = false;
		mutex_.Unlock();
	}
	void Open(){
		mutex_.Lock();
		opened_ = true;
		mutex_.Signal();
		mutex_.Unlock();
	}

};

class Th1 : public ick::Thread{

public:
	ThreadGate * gate_;
	ick::Mutex * x_mutex_;
	int * x;

	Th1(){
	}

	virtual void Run(){
		gate_->Pass();
		x_mutex_->Lock();
		*x = *x + 1;
		x_mutex_->Signal();
		x_mutex_->Unlock();
	}
};

TEST_F(WaitTest, signal){
	ick::Mutex mutex;
	ThreadGate gate;
	int x = 0;
	int n = 16;
	ick::Array<Th1*> ths(n);
	for (int i = 0; i < n; i++){
		ths[i] = ICK_NEW(Th1);
		ths[i]->gate_ = &gate;
		ths[i]->x_mutex_ = &mutex;
		ths[i]->x = &x;
		ths[i]->Start();
	}

	EXPECT_EQ(0, x);

	for (int i = 0; i < n; i++){
		mutex.Lock();
		int o_x = x;
		gate.Open();
		while (o_x == x){ mutex.Wait(); }
		mutex.Unlock();

		EXPECT_EQ(i + 1, x);
	}

	for (int i = 0; i < n; i++){
		ths[i]->Join();
		ICK_DELETE(ths[i]);
	}
}