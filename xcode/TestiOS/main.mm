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


