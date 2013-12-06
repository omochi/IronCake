//
//  ICKAllocatorTest.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//


#import <XCTest/XCTest.h>
#include <ick/ick.h>

@interface ICKAllocatorTest : XCTestCase

@end

@implementation ICKAllocatorTest

- (void)setUp
{
    [super setUp];
	struct ick::StartupInfo info = { NULL };
	ick::Startup(info);
}

- (void)tearDown
{
	ick::Shutdown();
    [super tearDown];
}

- (void)test1{
	ick::MallocAllocator ma;
	void * p = ma.Allocate(128,32);
	XCTAssertNotEqual(p, NULL);
	XCTAssertTrue(((uintptr_t)p & 0x0F) == 0x0);
	ma.Free(p);
}

- (void)test2{
	ick::DebugAllocator * allocator = ICK_NEW1(ick::DebugAllocator, ick::g_static_allocator);
	XCTAssertEqual(allocator->info_list()->num(), 0);
	
	int * a = ICK_ALLOC_A(allocator, int, 10);
	XCTAssertEqual(allocator->info_list()->num(), 1);
	
	int * b = ICK_ALLOC_A(allocator, int, 10);
	XCTAssertEqual(allocator->info_list()->num(), 2);
	
	ick::DebugAllocator::Node * n1 = allocator->info_list()->first();
	XCTAssertEqual((void*)a, n1->value().user);
	
	ick::DebugAllocator::Node * n2 = n1->next();
	XCTAssertEqual((void*)b, n2->value().user);
	
	allocator->Dump();
	
	ICK_FREE_A(allocator, a);
	XCTAssertEqual(allocator->info_list()->num(), 1);
	
	ICK_FREE_A(allocator, b);
	XCTAssertEqual(allocator->info_list()->num(), 0);
	
	
	ICK_DELETE(allocator);
}

-(void)test3{
	ick::DebugAllocator * allocator1 = ICK_NEW1(ick::DebugAllocator, ick::g_static_allocator);
	ICK_LOG_INFO("dump1");
	XCTAssertEqual(allocator1->info_list()->num(), 0);
	allocator1->Dump();
	
	ick::DebugAllocator * allocator2 = ICK_NEW1_A(allocator1, ick::DebugAllocator, allocator1);
	ICK_LOG_INFO("dump2");
	XCTAssertNotEqual(allocator1->info_list()->num(), 0);
	allocator1->Dump();
	
	int * a = ICK_ALLOC_A(allocator2, int, 1);
	
	ICK_LOG_INFO("dump3");
	allocator1->Dump();
	XCTAssertNotEqual(allocator1->info_list()->num(), 0);
	
	ICK_FREE_A(allocator2, a);
	
	ICK_LOG_INFO("dump4");
	allocator1->Dump();
	XCTAssertNotEqual(allocator1->info_list()->num(), 0);
	
	ICK_DELETE_A(allocator1,allocator2);
	
	ICK_LOG_INFO("dump5");
	allocator1->Dump();
	XCTAssertEqual(allocator1->info_list()->num(), 0);
	
	ICK_DELETE(allocator1);
}

-(void)test4{
	ick::DebugAllocator * allocator = ICK_NEW1(ick::DebugAllocator, ick::g_static_allocator);

	int * a = ICK_ALLOC_A(allocator, int, 3);
	//わざとはみ出る
	for(int i=0;i<=3;i++){
		a[i] = i;
	}
	
	ick::DebugAllocator::Node * node;
	bool ok = allocator->CheckSignatures(&node);
	XCTAssertFalse(ok);
	if(!ok){
		//オーバーフロー検出
		XCTAssertEqual((void *)a, node->value().user);
	}
	
	ICK_DELETE(allocator);
}

@end
