#include "test_base.h"

class LinkedListTest : public TestBase{
protected:
	virtual void SetUp(){
		TestBase::SetUp();
	}
	virtual void TearDown(){
		TestBase::TearDown();
	}
};

TEST_F(LinkedListTest, test1){
	ick::LinkedList<int> list;
	EXPECT_EQ(0, list.num());
	EXPECT_EQ(nullptr, list.first());
	EXPECT_EQ(nullptr, list.last());

	list.InsertLast(1);
	EXPECT_EQ(1, list.num());
	list.InsertLast(2);
	EXPECT_EQ(2, list.num());
	list.InsertLast(3);
	EXPECT_EQ(3, list.num());
	list.InsertLast(4);
	EXPECT_EQ(4, list.num());

	ick::LinkedListNode<int> * n1 = list.first();
	ick::LinkedListNode<int> * n2 = n1->next();
	ick::LinkedListNode<int> * n3 = n2->next();
	ick::LinkedListNode<int> * n4 = n3->next();

	EXPECT_EQ(nullptr, n1->prev());
	EXPECT_EQ(1, n1->value());
	EXPECT_EQ(n2, n1->next());
	EXPECT_EQ(n1, n2->prev());
	EXPECT_EQ(2, n2->value());
	EXPECT_EQ(n3, n2->next());
	EXPECT_EQ(n2, n3->prev());
	EXPECT_EQ(3, n3->value());
	EXPECT_EQ(n4, n3->next());
	EXPECT_EQ(n3, n4->prev());
	EXPECT_EQ(4, n4->value());
	EXPECT_EQ(nullptr, n4->next());

	n1->set_value(5);
	EXPECT_EQ(5, n1->value());

	list.Remove(n3);
	EXPECT_EQ(3, list.num());
	EXPECT_EQ(n4, n2->next());
	EXPECT_EQ(n2, n4->prev());

	list.InsertFirst(6);
	EXPECT_EQ(4, list.num());
	EXPECT_EQ(6, list.first()->value());
	EXPECT_EQ(n1, list.first()->next());
	EXPECT_EQ(n1->prev(), list.first());

	list.InsertLast(7);
	EXPECT_EQ(5, list.num());
	EXPECT_EQ(7, list.last()->value());
	EXPECT_EQ(n4, list.last()->prev());
	EXPECT_EQ(n4->next(), list.last());

	list.InsertBefore(n2, 8);
	EXPECT_EQ(6, list.num());
	EXPECT_EQ(8, n1->next()->value());
	EXPECT_EQ(8, n2->prev()->value());

	list.InsertAfter(n2, 9);
	EXPECT_EQ(7, list.num());
	EXPECT_EQ(9, n2->next()->value());
	EXPECT_EQ(9, n4->prev()->value());

	list.Remove(list.last());
	EXPECT_EQ(6, list.num());
	list.Remove(list.last());
	EXPECT_EQ(5, list.num());
	list.Remove(list.last());
	EXPECT_EQ(4, list.num());
	list.Remove(list.last());
	EXPECT_EQ(3, list.num());
	list.Remove(list.last());
	EXPECT_EQ(2, list.num());
	list.Remove(list.last());
	EXPECT_EQ(1, list.num());
	list.Remove(list.last());
	EXPECT_EQ(0, list.num());

	EXPECT_EQ(nullptr, list.first());
	EXPECT_EQ(nullptr, list.last());

	list.InsertLast(1);
	list.InsertLast(2);
	list.InsertLast(3);
	list.InsertLast(4);
	EXPECT_EQ(4, list.num());

	list.Clear();
	EXPECT_EQ(0, list.num());
	EXPECT_EQ(nullptr, list.first());
	EXPECT_EQ(nullptr, list.last());
}

