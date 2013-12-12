//
//  main.m
//  iOSTest
//
//  Created by おもちメタル on 2013/12/12.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <gtest/gtest.h>

#import "ICKTestAppDelegate.h"

int main(int argc, char **argv){
	testing::InitGoogleTest(&argc, argv);
	return UIApplicationMain(argc, argv, nil, NSStringFromClass([ICKTestAppDelegate class]));
}

//#include "gtest_main.cc"

//#include <stdio.h>
//
//
//
//#include "gtest/gtest.h"
//
//GTEST_API_ int main(int argc, char **argv) {
//	printf("Running main() from gtest_main.cc\n");
//	testing::InitGoogleTest(&argc, argv);
//	return RUN_ALL_TESTS();
//}

