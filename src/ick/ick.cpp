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
	MallocAllocator g_malloc_allocator;
	
	bool Startup(const struct StartupInfo & info){
		if(startedup){
			ICK_LOG_ERROR("already startedup");
			return false;
		}
		startedup = true;
		g_startup_info = info;
		
		Allocator * allocator;
		
		if(info.allocator){
			allocator = info.allocator;
		}else{
			allocator = & g_malloc_allocator;
		}
		
		if(info.memory_debug){
			allocator = ICK_NEW1_A(allocator, DebugAllocator, allocator);
		}
		g_static_allocator = allocator;
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
			DebugAllocator * debug_allocator = (ick::DebugAllocator *)g_static_allocator;
			Allocator * allocator = debug_allocator->allocator();
			ICK_DELETE_A(allocator, debug_allocator);
		}
		
		startedup = false;
		g_static_allocator = NULL;
		return true;
	}
}