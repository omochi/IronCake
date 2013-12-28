//
//  ick.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "ick.h"

#ifdef ICK_WINDOWS
#	include <mmsystem.h>
#endif

namespace ick{
	bool g_startedup = false;

	StartupConfig::StartupConfig(){
		allocator = NULL;
		memory_debug = false;
#ifdef ICK_APP_GLFW
		init_glfw = true;
#endif
#ifdef ICK_WINDOWS
		do_timeBeginPeriod = true;
#endif
	}
	StartupConfig g_startup_config;
	StartupConfig g_used_startup_config;
	
	bool Startup(){
		if(g_startedup){
			ICK_LOG_ERROR("already startedup");
			return false;
		}

		//使った設定を保存する
		g_used_startup_config = g_startup_config;
					
		StartupConfig & config = g_used_startup_config;
		
		if(config.allocator){
			set_static_allocator(config.allocator);
		}else{
			set_static_allocator(new MallocAllocator());
		}
		
		if(config.memory_debug){
			set_static_allocator(ICK_NEW(DebugAllocator, static_allocator()));
		}
		
#ifdef ICK_APP_GLFW
		if(config.init_glfw){
			if (!glfwInit()) {
				ICK_LOG_ERROR("glfwInit");
				return false;
			}
		}
#endif
#ifdef ICK_WINDOWS
		if(config.do_timeBeginPeriod){
			if (timeBeginPeriod(1)){
				ICK_LOG_ERROR("timeBeginPeriod");
				return false;
			}
		}
#endif
		
		g_startedup = true;
		return true;
	}
	bool IsStartedup() {
		return g_startedup;
	}
	bool Shutdown(){
		if(!g_startedup){
			ICK_LOG_ERROR("has not startedup");
			return false;
		}
		StartupConfig & config = g_used_startup_config;
		
#ifdef ICK_WINDOWS
		if(config.do_timeBeginPeriod){
			if (timeEndPeriod(1)){
				ICK_LOG_ERROR("timeEndPeriod");
				return false;
			}
		}
#endif
#ifdef ICK_APP_GLFW
		if(config.init_glfw){
			glfwTerminate();
		}
#endif
	
		if(config.memory_debug){
			DebugAllocator * debug_allocator = static_debug_allocator();
			set_static_allocator(debug_allocator->allocator());
			ICK_DELETE(debug_allocator);
		}

		if(!config.allocator){
			delete static_allocator();
		}
		set_static_allocator(NULL);
		
		g_startedup = false;
		return true;
	}
}

