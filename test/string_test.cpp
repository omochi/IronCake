#include "test_base.h"

class StringTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

TEST_F(StringTest, test1){
	ick::String s1;
	EXPECT_EQ(0, s1.num());
	ick::String s2("abc");
	EXPECT_EQ(3, s2.num());
	EXPECT_STREQ("abc", s2.cstr());
	ick::String s3(s2);
	EXPECT_EQ(3, s3.num());
	EXPECT_STREQ("abc", s3.cstr());
}

TEST_F(StringTest, operator_eq){
	ick::String s1("abc");
	EXPECT_TRUE(ick::String("abc") == s1);
	EXPECT_FALSE(ick::String("ab") == s1);
	EXPECT_TRUE(ick::String("ab") != s1);
	EXPECT_FALSE(ick::String("abc") != s1);
}


TEST_F(StringTest, test2){
	ick::String s1("abc");
	s1.Append(ick::String("def"));
	EXPECT_EQ(6, s1.num());
	EXPECT_STREQ("abcdef", s1.cstr());

	s1.Insert(0, ick::String("gh"));
	EXPECT_EQ(8, s1.num());
	EXPECT_STREQ("ghabcdef", s1.cstr());

	s1.Insert(3, ick::String("ijk"));
	EXPECT_EQ(ick::String("ghaijkbcdef"),s1);

	s1.Remove(0, 2);
	EXPECT_EQ(ick::String("aijkbcdef"),s1);

	s1.Remove(6, 3);
	EXPECT_EQ(ick::String("aijkbc"),s1);


}

