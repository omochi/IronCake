//
//  ick.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "ick.h"

namespace ick{
	bool startedup = false;
	struct StartupInfo g_startup_info;
	
	bool Startup(const struct StartupInfo & info){
		if(startedup){
			ICK_LOG_ERROR("already startedup");
			return false;
		}
		startedup = true;
		g_startup_info = info;
			
		if(info.allocator){
			set_static_allocator(info.allocator);
		}else{
			set_static_allocator(new MallocAllocator());
		}
		
		if(info.memory_debug){
			set_static_allocator(ICK_NEW(DebugAllocator, static_allocator()));
		}
		return true;
	}
	bool IsStartedup() {
		return startedup;
	}
	bool Shutdown(){
		if(!startedup){
			ICK_LOG_ERROR("has not startedup");
			return false;
		}
		
		struct StartupInfo info = g_startup_info;
		
		if(info.memory_debug){
			DebugAllocator * debug_allocator = static_debug_allocator();
			set_static_allocator(debug_allocator->allocator());
			ICK_DELETE(debug_allocator);
		}

		if(!info.allocator){
			delete static_allocator();
		}
		
		startedup = false;
		set_static_allocator(NULL);
		return true;
	}
}