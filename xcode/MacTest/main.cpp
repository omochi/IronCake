//
//  main.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/12.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include <stdio.h>

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


