#include "test_base.h"

class MutexTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};


void f2(ick::Mutex * mutex, int * x){
	mutex->Lock();
	EXPECT_EQ(0, *x);
	*x = *x + 1;
	ick::Sleep(0.010);
	EXPECT_EQ(1, *x);
	*x = *x - 1;
	EXPECT_EQ(0, *x);
	mutex->Unlock();
}

TEST_F(MutexTest, mutex){
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

void f2_2(ick::Mutex * mutex, int * x){
	ick::ScopedLock slk(*mutex);
	EXPECT_EQ(0, *x);
	*x = *x + 1;
	ick::Sleep(0.010);
	EXPECT_EQ(1, *x);
	*x = *x - 1;
	EXPECT_EQ(0, *x);
}

TEST_F(MutexTest, scoped_lock){
	ick::Array<ick::Thread *> ths(16);
	ick::Mutex mutex;
	int x = 0;
	for(int i = 0; i < ths.num(); i++){
		ths[i] = ICK_NEW(ick::FunctionThread, ick::FunctionBind2(f2_2, &mutex, &x));
		ths[i]->Start();
	}
	for(int i = 0; i < ths.num(); i++){
		ths[i]->Join();
		ICK_DELETE(ths[i]);
	}
}

void f3_wait(ick::Mutex * mutex, int * x, int n){
	mutex->Lock();
	while (true){
		if (*x == n){ break; }
		mutex->Wait();
	}
	EXPECT_EQ(n, *x);
	mutex->Unlock();
}

void f3_notify(ick::Mutex * mutex, int * x){
	mutex->Lock();
	*x = *x + 1;
	mutex->Notify();
	mutex->Unlock();
}

TEST_F(MutexTest, cond){
	ick::Array<ick::Thread *> ws(16);
	ick::Array<ick::Thread *> ns(ws.num());
	ick::Mutex mutex;
	int x = 0;
	for(int i = 0; i < ws.num(); i++){
		ws[i] = ICK_NEW(ick::FunctionThread, ick::FunctionBind3(f3_wait, &mutex, &x, ws.num()));
		ws[i]->Start();
	}
	ick::Sleep(0.010);
	for(int i = 0; i< ns.num(); i++){
		ns[i] = ICK_NEW(ick::FunctionThread, ick::FunctionBind2(f3_notify, &mutex, &x));
		ns[i]->Start();
	}
	for(int i = 0; i< ns.num(); i++){
		ns[i]->Join();
		ICK_DELETE(ns[i]);
	}
	for(int i = 0; i < ws.num(); i++){
		ws[i]->Join();
		ICK_DELETE(ws[i]);
	}
}
