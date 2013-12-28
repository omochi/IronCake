//
//  ick.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "ick.h"

namespace ick{
	bool g_startedup = false;

	struct StartupConfig g_startup_config = {
		NULL,
		false
	};
	struct StartupConfig g_used_startup_config;
	
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