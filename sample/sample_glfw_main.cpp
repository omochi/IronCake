#include "sample_glfw_main.h"

int SampleAppMain(int argc, const char * argv[]){
	(void)argc; (void)argv;
	
	ick::g_startup_config.memory_debug = true;
	if(!ick::Startup()){
		fprintf(stderr,"ick::Startup failed");
		return EXIT_SUCCESS;
	}
	
	ick::Application * app = ICK_NEW(ick::Application, ICK_NEW(SampleAppController), true);
	app->GLFWMain();
	ICK_DELETE(app);
	
	if(!ick::Shutdown()){
		fprintf(stderr, "ick::Shutdown failed");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}


