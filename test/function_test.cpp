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

TEST_F(FunctionTest, bind1){
	ick::Function<int (*)(int)> g1 = f1;
	ick::Function<int (*)()> g2 = ick::FunctionBind(g1, 2);
	ick::Function<int (*)()> g3 = ick::FunctionBind(f1, 3);
	
	EXPECT_EQ(2, g1(1));
	EXPECT_EQ(4, g2());
	EXPECT_EQ(6, g3());
	
}

static double f2(char a, int b, long c, float d){
	return static_cast<double>(static_cast<float>(a) +
							   static_cast<float>(b) +
							   static_cast<float>(c) +
							   static_cast<float>(d)
							   );
}

TEST_F(FunctionTest, bind2){
	
	EXPECT_EQ(1234, f2(4, 30, 200, 1000));
	
	ick::Function<double (*)(int,long,float)> g1 = ick::FunctionBind(f2, (char)5);
	EXPECT_EQ(1235, g1(30, 200, 1000));
	
	ick::Function<double (*)(long,float)> g2 = ick::FunctionBind(g1, (int)40);
	EXPECT_EQ(1245, g2(200, 1000));
	
	ick::Function<double (*)(float)> g3 = ick::FunctionBind(g2, (long)300);
	EXPECT_EQ(1345, g3(1000));
	
	ick::Function<double (*)()> g4 = ick::FunctionBind(g3, (float)2000);
	EXPECT_EQ(2345, g4());
	
}

TEST_F(FunctionTest, bind3){
		
	ick::Function<double (*)(long,float)> g1 = ick::FunctionBind(f2, (char)5, (int)40);
	EXPECT_EQ(1245, g1(200, 1000));
	
	ick::Function<double (*)()> g2 = ick::FunctionBind(g1, (long)300, (float)2000);
	EXPECT_EQ(2345, g2());
	
	ick::Function<double (*)()> g3 = ick::FunctionBind(f2, (char)5, (int)40, (long)300, (float)2000);
	EXPECT_EQ(2345, g3());
	
	
}

class A{
public:
	int a;
	int b;
	int mth(){
		return a+b;
	}
	int mth2(int c){
		return mth() + c;
	}
};

TEST_F(FunctionTest, method){
	A a;
	a.a = 1;
	a.b = 2;
	ick::Function<int (*)()> g1 = ick::FunctionBind(&A::mth, &a);
	EXPECT_EQ(3, g1());
	ick::Function<int (*)(int)> g2 = ick::FunctionBind(&A::mth2, &a);
	EXPECT_EQ(6, g2(3));
	ick::Function<int (*)()> g3 = ick::FunctionBind(g2, 3);
	EXPECT_EQ(6, g3());
	ick::Function<int (*)()> g4 = ick::FunctionBind(ick::FunctionBind(&A::mth2, &a),3);
	EXPECT_EQ(6, g4());
	
}

