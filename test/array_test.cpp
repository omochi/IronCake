#include "test_base.h"

class ArrayTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

TEST_F(ArrayTest, test1){
	ick::Array<int> a1;
	EXPECT_EQ(0, a1.num());

	ick::Array<int> a2(3);
	EXPECT_EQ(3, a2.num());
	a2[0] = 0;
	a2[1] = 1;
	a2[2] = 2;
	EXPECT_EQ(0, a2[0]);
	EXPECT_EQ(1, a2[1]);
	EXPECT_EQ(2, a2[2]);
}

TEST_F(ArrayTest, test2){
	ick::Array<int> a1 = ick::ArrayMake(0, 1, 2, 3);
	EXPECT_EQ(4, a1.num());
	EXPECT_EQ(0, a1[0]);
	EXPECT_EQ(1, a1[1]);
	EXPECT_EQ(2, a1[2]);
	EXPECT_EQ(3, a1[3]);
}

TEST_F(ArrayTest, test3){
	ick::Array<int> a1 = ick::ArrayMake
	(0, 1, 2, 3);
	a1.Splice(0, 0, ick::Array<int>());
	EXPECT_EQ(ick::ArrayMake(0, 1, 2, 3), a1);

	a1.Splice(0, 1, ick::Array<int>());
	EXPECT_EQ(ick::ArrayMake(1, 2, 3), a1);

	a1.Splice(1, 2, ick::Array<int>());
	EXPECT_EQ(ick::ArrayMake(1), a1);

	a1.Splice(0, 0, ick::ArrayMake(2, 3));
	EXPECT_EQ(ick::ArrayMake(2, 3, 1), a1);

	a1.Splice(1, 0, ick::ArrayMake(4, 5));
	EXPECT_EQ(ick::ArrayMake(2, 4, 5, 3, 1), a1);

	a1.Splice(5, 0, ick::ArrayMake(6));
	EXPECT_EQ(ick::ArrayMake(2, 4, 5, 3, 1, 6), a1);

	a1.Splice(1, 4, ick::ArrayMake(7, 8, 9));
	EXPECT_EQ(ick::ArrayMake(2, 7, 8, 9, 6), a1);

	a1.Splice(0, 2, ick::ArrayMake(10, 11, 12));
	EXPECT_EQ(ick::ArrayMake(10, 11, 12, 8, 9, 6), a1);

	EXPECT_EQ(ick::Array<int>(),a1.Slice(0, 0));
	EXPECT_EQ(ick::ArrayMake(10, 11),a1.Slice(0, 2));
	EXPECT_EQ(ick::ArrayMake(11, 12, 8),a1.Slice(1, 3));
	EXPECT_EQ(ick::ArrayMake(8, 9, 6),a1.Slice(3, 3));
}

TEST_F(ArrayTest, test4){
	ick::Array<int> a1 = ick::ArrayMake(0, 1);
	a1.Append(2);
	EXPECT_EQ(ick::ArrayMake(0, 1, 2), a1);
	a1.Append(ick::ArrayMake(3, 4));
	EXPECT_EQ(ick::ArrayMake(0, 1, 2, 3, 4), a1);
	a1.Insert(0, 5);
	EXPECT_EQ(ick::ArrayMake(5, 0, 1, 2, 3, 4), a1);
	a1.Insert(1, ick::ArrayMake(6, 7));
	EXPECT_EQ(ick::ArrayMake(5, 6, 7, 0, 1, 2, 3, 4), a1);
	a1.Remove(3, 2);
	EXPECT_EQ(ick::ArrayMake(5, 6, 7, 2, 3, 4), a1);
	a1.Remove(5);
	EXPECT_EQ(ick::ArrayMake(5, 6, 7, 2, 3), a1);
}
