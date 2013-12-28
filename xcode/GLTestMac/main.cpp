//
//  main.cpp
//  GLTestMac
//
//  Created by おもちメタル on 2013/12/26.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "GLTestApp.h"

ick::Application * g_application;

bool ickMain();
bool glfwMain();

int main(int argc, const char * argv[]){
	ick::g_startup_config.memory_debug = true;
	if(!ick::Startup()){
		printf("ick::Startup failed");
		return EXIT_FAILURE;
	}
	bool ok = ickMain();
	if(!ick::Shutdown()){
		printf("ick::Shutdown failed");
		return EXIT_FAILURE;
	}
	return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

bool ickMain(){
	if (!glfwInit()) {
		ICK_LOG_ERROR("glfwInit failed");
		return false;
	}
	bool ok = glfwMain();
	glfwTerminate();
	return ok;
}

bool glfwMain(){	
	g_application = ICK_NEW(ick::Application);
	g_application->set_delegate(ICK_NEW(GLTestAppDelegate));
	
	glfwWindowHint(GLFW_RESIZABLE, 0);
    GLFWwindow * window = glfwCreateWindow(640, 480, "IronCake GL Test", NULL, NULL);
    if (!window){
		ICK_LOG_ERROR("glfwCreateWindow failed");
		return false;
    }
	
	g_application->set_glfw_window(window);
		
	g_application->Launch();
	
    glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	

    while (!glfwWindowShouldClose(window)){		
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
        glfwSwapBuffers(window);
		glfwWaitEvents();
    }
	
	g_application->Terminate();
	
	ICK_DELETE(g_application->delegate());
	ICK_DELETE(g_application);
	
	return true;
}
