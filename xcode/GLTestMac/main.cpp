//
//  main.cpp
//  GLTestMac
//
//  Created by おもちメタル on 2013/12/26.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include <ick/ick.h>
#include <GLFW/glfw3.h>

ick::Application * g_application;

bool ickMain();
bool glfwMain();

int main(int argc, const char * argv[]){
	ick::StartupInfo info = {NULL,true};
	if(!ick::Startup(info)){
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
	glfwWindowHint(GLFW_RESIZABLE, 0);
    GLFWwindow * window = glfwCreateWindow(640, 480, "IronCake GL Test", NULL, NULL);
    if (!window){
		ICK_LOG_ERROR("glfwCreateWindow failed");
		return false;
    }
	
	g_application = ICK_NEW(ick::Application);
	g_application->Launch();
	
    glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	
	double prev_sec_clock = ick::ClockGet();
	int sec_frame_count = 0;
    while (!glfwWindowShouldClose(window)){
		sec_frame_count++;
		double sec_clock = ick::ClockGet();
		if(sec_clock - prev_sec_clock >= 1.0){
			ICK_LOG_INFO("fps: %d\n",sec_frame_count);
			sec_frame_count = 0;
			prev_sec_clock = sec_clock;
		}
		
		glClearColor(0, 1, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		
        glfwSwapBuffers(window);
		glfwWaitEvents();
    }
	
	g_application->Terminate();
	ICK_DELETE(g_application);
	
	return true;
}
