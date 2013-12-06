//
//  ICKTestBase.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/05.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import "ICKTestBase.h"

@implementation ICKTestBase

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

@end
