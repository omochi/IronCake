//
//  ICKStringTest.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/09.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import <XCTest/XCTest.h>

#import "ICKTestBase.h"

@interface ICKStringTest : ICKTestBase

@end

@implementation ICKStringTest

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
	ick::String s1;
	XCTAssertEqual(s1.num(), 0);
	ick::String s2("abc");
	XCTAssertEqual(s2.num(), 3);
	XCTAssertTrue(!strcmp("abc", s2.cstr()));
	ick::String s3(s2);
	XCTAssertEqual(s3.num(), 3);
	XCTAssertTrue(!strcmp("abc", s3.cstr()));
	
	XCTAssertTrue(ick::String("abc") == s2);
	XCTAssertFalse(ick::String("abc") != s2);
	XCTAssertFalse(ick::String("ab") == s2);
	XCTAssertTrue(ick::String("ab") != s2);
}

- (void)test2{
	ick::String s1("abc");
	s1.Append(ick::String("def"));
	XCTAssertEqual(s1.num(), 6);
	XCTAssertTrue(!strcmp("abcdef", s1.cstr()));
	
	s1.Insert(0, ick::String("gh"));
	XCTAssertEqual(s1.num(), 8);
	XCTAssertTrue(!strcmp("ghabcdef", s1.cstr()));
	
	s1.Insert(3, ick::String("ijk"));
	XCTAssertTrue(s1 == ick::String("ghaijkbcdef"));
	
	s1.Remove(0, 2);
	XCTAssertTrue(s1 == ick::String("aijkbcdef"));
	
	s1.Remove(6, 3);
	XCTAssertTrue(s1 == ick::String("aijkbc"));
	

}

@end
