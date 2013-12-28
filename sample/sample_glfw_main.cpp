#include "sample_glfw_main.h"

#ifdef ICK_APP_GLFW

ick::Application * g_application;

bool SampleAppMain(){
	ick::g_startup_config.memory_debug = true;
	if(!ick::Startup()){
		printf("ick::Startup failed");
		return false;
	}
	
	g_application = ICK_NEW(ick::Application, ICK_NEW(SampleAppController));
	
	glfwWindowHint(GLFW_RESIZABLE, 0);
    GLFWwindow * window = glfwCreateWindow(640, 480, "IronCake GL Test", NULL, NULL);
    if (!window){ ICK_ABORT("glfwCreateWindow"); }
	
	g_application->set_glfw_window(window);
	g_application->Launch();
	
    while (!glfwWindowShouldClose(window)){
		glfwWaitEvents();
    }
	
	g_application->Terminate();
	
	ICK_DELETE(g_application->controller());
	ICK_DELETE(g_application);
	
	if(!ick::Shutdown()){
		printf("ick::Shutdown failed");
		return false;
	}
	
	return true;
}

#endif

