//
//  main.cpp
//  GLTestMac
//
//  Created by おもちメタル on 2013/12/26.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "GLTestApp.h"

ick::Application * g_application;

bool AppMain();

int main(int argc, const char * argv[]){
	(void)argc;
	(void)argv;
	ick::g_startup_config.memory_debug = true;
	if(!ick::Startup()){
		printf("ick::Startup failed");
		return EXIT_FAILURE;
	}
	bool ok = AppMain();
	if(!ick::Shutdown()){
		printf("ick::Shutdown failed");
		return EXIT_FAILURE;
	}
	return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

bool AppMain(){
	g_application = ICK_NEW(ick::Application, ICK_NEW(GLTestAppController));
	
	glfwWindowHint(GLFW_RESIZABLE, 0);
    GLFWwindow * window = glfwCreateWindow(640, 480, "IronCake GL Test", NULL, NULL);
    if (!window){
		ICK_LOG_ERROR("glfwCreateWindow failed");
		return false;
    }
	glfwMakeContextCurrent(window);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	g_application->set_glfw_window(window);
		
	g_application->Launch();
	


	
    while (!glfwWindowShouldClose(window)){		

		glfwWaitEvents();
    }
	
	g_application->Terminate();
	
	ICK_DELETE(g_application->controller());
	ICK_DELETE(g_application);
	
	return true;
}
