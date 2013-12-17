#include <gtest/gtest.h>
#include <ick/ick.h>

class AllocatorTest : public testing::Test {
protected:
	virtual void SetUp(){
		struct ick::StartupInfo info = { NULL, false };
		ick::Startup(info);
	}
	virtual void TearDown(){
		ick::Shutdown();
	}
};

TEST_F(AllocatorTest, test1){
	ick::MallocAllocator ma;
	void * p = ma.Allocate(128, 32);
	EXPECT_NE(nullptr, p);
	EXPECT_EQ(0x0u, (uintptr_t)p & 0x0F);
	ma.Free(p);
}

TEST_F(AllocatorTest, test2){

	ick::DebugAllocator * allocator = ICK_NEW1(ick::DebugAllocator, ick::static_allocator());
	EXPECT_EQ(0, allocator->info_list()->num());

	int * a = ICK_ALLOC_A(allocator, int, 10);
	EXPECT_EQ(1, allocator->info_list()->num());

	int * b = ICK_ALLOC_A(allocator, int, 10);
	EXPECT_EQ(2, allocator->info_list()->num());

	ick::DebugAllocator::Node * n1 = allocator->info_list()->first();
	EXPECT_EQ(n1->value().user, a);

	ick::DebugAllocator::Node * n2 = n1->next();
	EXPECT_EQ(n2->value().user, b);

	//allocator->Dump();

	ICK_FREE_A(allocator, a);
	EXPECT_EQ(1, allocator->info_list()->num());

	ICK_FREE_A(allocator, b);
	EXPECT_EQ(0, allocator->info_list()->num());

	ICK_DELETE(allocator);

}

TEST_F(AllocatorTest, test3){
	ick::DebugAllocator * allocator1 = ICK_NEW1(ick::DebugAllocator, ick::static_allocator());
	EXPECT_EQ(0, allocator1->info_list()->num());

	ick::DebugAllocator * allocator2 = ICK_NEW1_A(allocator1, ick::DebugAllocator, allocator1);
	EXPECT_NE(0, allocator1->info_list()->num());

	int * a = ICK_ALLOC_A(allocator2, int, 1);
	EXPECT_NE(0, allocator1->info_list()->num());

	ICK_FREE_A(allocator2, a);
	EXPECT_NE(0, allocator1->info_list()->num());

	ICK_DELETE_A(allocator1, allocator2);
	EXPECT_EQ(0, allocator1->info_list()->num());

	ICK_DELETE(allocator1);
}

TEST_F(AllocatorTest, test4){
	ick::DebugAllocator * allocator = ICK_NEW1(ick::DebugAllocator, ick::static_allocator());

	int * a = ICK_ALLOC_A(allocator, int, 3);
	//わざとはみ出る
	for (int i = 0; i <= 3; i++){
		a[i] = i;
	}

	ick::DebugAllocator::Node * node;
	bool ok = allocator->CheckSignatures(&node);
	EXPECT_FALSE(ok);

	//オーバーフロー検出
	EXPECT_EQ((void *)a, node->value().user);
	
	ICK_DELETE(allocator);
}
