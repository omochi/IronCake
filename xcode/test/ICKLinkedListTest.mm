//
//  ICKLinkedListTest.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <ick/ick.h>

@interface ICKLinkedListTest : XCTestCase

@end

@implementation ICKLinkedListTest

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
	ick::LinkedList<int> list;
	XCTAssertEqual(list.num(), 0);
	
	list.InsertLast(1);
	list.InsertLast(2);
	list.InsertLast(3);
	list.InsertLast(4);
	XCTAssertEqual(list.num(), 4);
	
	
}

@end
