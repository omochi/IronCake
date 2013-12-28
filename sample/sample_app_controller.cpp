//
//  GLTestApp.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/29.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "sample_app_controller.h"

SampleAppController::~SampleAppController(){
}
void SampleAppController::ApplicationDidLaunch(){
	sec_frame_count_ = 0;
	prev_sec_clock_ = ick::ClockGet();
	frame_count_ = 0;
}
void SampleAppController::ApplicationWillTerminate(){
}
void SampleAppController::ApplicationOnUpdate(){
	sec_frame_count_++;
	double clock = ick::ClockGet();
	if(clock - prev_sec_clock_ >= 1.0){
		ICK_LOG_INFO("fps: %2d\n", sec_frame_count_);
		prev_sec_clock_ = clock;
		sec_frame_count_ = 0;
	}
	
	frame_count_++;
}
void SampleAppController::ApplicationOnRender(){
	int mod_fc = frame_count_ % 6;
	if(mod_fc == 0){
		glClearColor(1, 0, 0, 1);
	}else if(mod_fc == 1){
		glClearColor(1, 1, 0, 1);
	}else if(mod_fc == 2){
		glClearColor(0, 1, 0, 1);
	}else if(mod_fc == 3){
		glClearColor(0, 1, 1, 1);
	}else if(mod_fc == 4){
		glClearColor(0, 0, 1, 1);
	}else if(mod_fc == 5){
		glClearColor(1, 0, 1, 1);
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
}

