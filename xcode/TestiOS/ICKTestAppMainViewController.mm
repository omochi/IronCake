//
//  ICKTestAppMainViewController.m
//  IronCake
//
//  Created by おもちメタル on 2013/12/13.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#import "ICKTestAppMainViewController.h"

#include <gtest/gtest.h>

@interface ICKTestAppMainViewController ()
@property(nonatomic,assign)BOOL testStarted;
@property(nonatomic,strong)IBOutlet UITextView * textView;

@end

@implementation ICKTestAppMainViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	_testStarted = NO;
}

-(void)viewDidAppear:(BOOL)animated{
	[super viewDidAppear:animated];
	self.textView.text = @"test running...";
	if(!_testStarted){
		_testStarted = YES;
		
		dispatch_async(dispatch_get_main_queue(), ^{
			NSLog(@"Test Start");
			testing::UnitTest * test = testing::UnitTest::GetInstance();
			(void)test->Run();
			
			NSString * report = [NSString stringWithFormat:
								 @"test case count: %d\n"
								 @"    succeeded  : %d\n"
								 @"    failed     : %d\n"
								 @"test count     : %d\n"
								 @"    succeeded  : %d\n"
								 @"    failed     : %d",
								 test->total_test_case_count(),
								 test->successful_test_case_count(),
								 test->failed_test_case_count(),
								 test->total_test_count(),
								 test->successful_test_count(),
								 test->failed_test_count()
								 ];
			
			self.textView.text = report;
		});
	}
	
}

-(IBAction)onQuitButton{
	exit(EXIT_SUCCESS);
}

@end
