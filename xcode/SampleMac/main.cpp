//
//  main.cpp
//  GLTestMac
//
//  Created by おもちメタル on 2013/12/26.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "sample_glfw_main.h"

int main(int argc, const char * argv[]){
	(void)argc;
	(void)argv;
	
	if(SampleAppMain()){
		return EXIT_SUCCESS;
	}else{
		return EXIT_FAILURE;
	}
}
