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
	XCTAssertEqual(list.num(), 1);
	list.InsertLast(2);
	XCTAssertEqual(list.num(), 2);
	list.InsertLast(3);
	XCTAssertEqual(list.num(), 3);
	list.InsertLast(4);
	XCTAssertEqual(list.num(), 4);
	
	ick::LinkedListNode<int> * n1 = list.first();
	ick::LinkedListNode<int> * n2 = n1->next();
	ick::LinkedListNode<int> * n3 = n2->next();
	ick::LinkedListNode<int> * n4 = n3->next();
	
	XCTAssertFalse(n1->prev());
	XCTAssertEqual(n1->value(), 1);
	XCTAssertEqual(n1->next(), n2);
	XCTAssertEqual(n2->prev(), n1);
	XCTAssertEqual(n2->value(), 2);
	XCTAssertEqual(n2->next(), n3);
	XCTAssertEqual(n3->prev(), n2);
	XCTAssertEqual(n3->value(), 3);
	XCTAssertEqual(n3->next(), n4);
	XCTAssertEqual(n4->prev(), n3);
	XCTAssertEqual(n4->value(), 4);
	XCTAssertFalse(n4->next());
	
	n1->set_value(5);
	XCTAssertEqual(n1->value(), 5);
	
	list.Remove(n3);
	XCTAssertEqual(list.num(), 3);
	XCTAssertEqual(n2->next(), n4);
	XCTAssertEqual(n4->prev(), n2);
}

@end
