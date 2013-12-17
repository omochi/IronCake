//
//  ICKTestAppDelegate.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/13.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import "ICKTestAppDelegate.h"

#import "ICKTestAppMainViewController.h"

@implementation ICKTestAppDelegate

-(BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions{

	(void)application;
	(void)launchOptions;
	
	self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	[self.window makeKeyAndVisible];
	
	ICKTestAppMainViewController * vc = [[ICKTestAppMainViewController alloc] initWithNibName:NSStringFromClass([ICKTestAppMainViewController class]) bundle:nil];
	self.window.rootViewController = vc;
	
	return YES;
}



@end
