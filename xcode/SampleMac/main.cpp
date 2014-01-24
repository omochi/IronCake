//
//  main.cpp
//  GLTestMac
//
//  Created by おもちメタル on 2013/12/26.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "../../sample/sample_app_controller.h"

ick::ApplicationController * ControllerConstruct(){
	return ICK_NEW(SampleAppController);
}

int main(int argc, const char * argv[]){
	ick::g_startup_config.memory_debug = true;
	return ick::ApplicationGLFWMain(argc, argv, &ControllerConstruct);
}

