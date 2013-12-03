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
	MallocAllocator mallocAllocator;
	
	bool Startup(const struct StartupInfo & info){
		if(startedup){
			ICK_LOG_ERROR("already startedup");
			return false;
		}
		if(info.allocator){
			g_static_allocator = info.allocator;
		}else{
			g_static_allocator = & mallocAllocator;
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
		g_static_allocator = NULL;
		return true;
	}
}