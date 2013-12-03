//
//  ICKAllocatorTest.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <ick/base/allocator.h>

@interface ICKAllocatorTest : XCTestCase

@end

@implementation ICKAllocatorTest

- (void)setUp
{
    [super setUp];
    // Put setup code here; it will be run once, before the first test case.
}

- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)test1{
	ick::MallocAllocator ma;
	void * p = ma.Allocate(128);
	XCTAssertNotEqual(p, NULL);
	ma.Free(p);
}

@end
