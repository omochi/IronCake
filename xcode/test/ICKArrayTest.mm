//
//  ICKArrayTest.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/07.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import "ICKTestBase.h"

@interface ICKArrayTest : ICKTestBase

@end

@implementation ICKArrayTest

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
	ick::Array<int> a1;
	XCTAssertEqual(a1.num(), 0);

	ick::Array<int> a2(3);
	XCTAssertEqual(a2.num(), 3);
	a2[0] = 0;
	a2[1] = 1;
	a2[2] = 2;
	XCTAssertEqual(a2[0], 0);
	XCTAssertEqual(a2[1], 1);
	XCTAssertEqual(a2[2], 2);
	
}

- (void)test2{
	ick::Array<int> a1 = ick::ArrayMake4(0,1,2,3);
	XCTAssertEqual(a1.num(), 4);
	XCTAssertEqual(a1[0], 0);
	XCTAssertEqual(a1[1], 1);
	XCTAssertEqual(a1[2], 2);
	XCTAssertEqual(a1[3], 3);
}

- (void)test3{
	ick::Array<int> a1 = ick::ArrayMake4(0,1,2,3);
	a1.Splice(0, 0, ick::Array<int>());
	XCTAssertTrue(a1 == ick::ArrayMake4(0,1,2,3));
	
	a1.Splice(0, 1, ick::Array<int>());
	XCTAssertTrue(a1 == ick::ArrayMake3(1,2,3));
	
	a1.Splice(1, 2, ick::Array<int>());
	XCTAssertTrue(a1 == ick::ArrayMake1(1));
	
	a1.Splice(0, 0, ick::ArrayMake2(2, 3));
	XCTAssertTrue(a1 == ick::ArrayMake3(2,3,1));
	
	a1.Splice(1, 0, ick::ArrayMake2(4, 5));
	XCTAssertTrue(a1 == ick::ArrayMake5(2,4,5,3,1));
	
	a1.Splice(5, 0, ick::ArrayMake1(6));
	XCTAssertTrue(a1 == ick::ArrayMake6(2,4,5,3,1,6));
	
	a1.Splice(1, 4, ick::ArrayMake3(7,8,9));
	XCTAssertTrue(a1 == ick::ArrayMake5(2,7,8,9,6));
	
	a1.Splice(0, 2, ick::ArrayMake3(10,11,12));
	XCTAssertTrue(a1 == ick::ArrayMake6(10,11,12,8,9,6));
	
	XCTAssertTrue(a1.Slice(0, 0) == ick::Array<int>());
	XCTAssertTrue(a1.Slice(0, 2) == ick::ArrayMake2(10,11));
	XCTAssertTrue(a1.Slice(1, 3) == ick::ArrayMake3(11,12,8));
	XCTAssertTrue(a1.Slice(3, 3) == ick::ArrayMake3(8,9,6));
}

- (void)test4{
	ick::Array<int> a1 = ick::ArrayMake2(0,1);
	a1.Append(2);
	XCTAssertTrue(a1 == ick::ArrayMake3(0,1,2));
	a1.Append(ick::ArrayMake2(3, 4));
	XCTAssertTrue(a1 == ick::ArrayMake5(0,1,2,3,4));
	a1.Insert(0, 5);
	XCTAssertTrue(a1 == ick::ArrayMake6(5,0,1,2,3,4));
	a1.Insert(1, ick::ArrayMake2(6,7));
	XCTAssertTrue(a1 == ick::ArrayMake8(5,6,7,0,1,2,3,4));
	a1.Remove(3, 2);
	XCTAssertTrue(a1 == ick::ArrayMake6(5,6,7,2,3,4));
	a1.Remove(5);
	XCTAssertTrue(a1 == ick::ArrayMake5(5,6,7,2,3));
}

@end
