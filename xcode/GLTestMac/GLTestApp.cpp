//
//  GLTestApp.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/29.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "GLTestApp.h"

GLTestAppController::~GLTestAppController(){
}
void GLTestAppController::ApplicationDidLaunch(ick::Application * application){
	(void)application;
	sec_frame_count_ = 0;
	prev_sec_clock_ = ick::ClockGet();
}
void GLTestAppController::ApplicationWillTerminate(ick::Application * application){
	(void)application;
}
void GLTestAppController::ApplicationOnUpdate(ick::Application * application){
	(void)application;
	
	sec_frame_count_++;
	double clock = ick::ClockGet();
	if(clock - prev_sec_clock_ >= 1.0){
		ICK_LOG_INFO("fps: %2d\n", sec_frame_count_);
		prev_sec_clock_ = clock;
		sec_frame_count_ = 0;

	}
	
}

