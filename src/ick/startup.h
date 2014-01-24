#pragma once

namespace ick{
	class Allocator;
	
	struct StartupConfig {
		Allocator * allocator; // = NULL
		bool memory_debug; // = false
#ifdef ICK_APP_GLFW
		bool init_glfw; // = true
#endif
#ifdef ICK_WINDOWS
		bool do_timeBeginPeriod; // = true
#endif
		StartupConfig();
	};
	//デフォルト値で初期化済み
	extern StartupConfig g_startup_config;
	bool Startup();
	bool IsStartedup();
	bool Shutdown();
}

