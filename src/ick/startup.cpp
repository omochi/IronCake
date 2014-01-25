#include "startup.h"

#include "base/allocator.h"
#include "base/debug_allocator.h"
#include "base/memory.h"
#include "base/log.h"
#include "base/string.h"

#ifdef ICK_WINDOWS
#	include <mmsystem.h>
#endif

namespace ick{
	bool g_startedup = false;
	
	StartupConfig::StartupConfig(){
		allocator = NULL;
		memory_debug = false;
#ifdef ICK_WINDOWS
		do_timeBeginPeriod = true;
#endif
	}
	StartupConfig g_startup_config;
	StartupConfig g_used_startup_config;
	
	bool Startup(){
		if(g_startedup){
			ICK_LOG_ERROR("already startedup\n");
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
			ICK_LOG_INFO("debug allocator enabled\n");
		}
		
#ifdef ICK_WINDOWS
		if(config.do_timeBeginPeriod){
			if (timeBeginPeriod(1)){
				ICK_LOG_ERROR("timeBeginPeriod failed\n");
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
			ICK_LOG_ERROR("has not startedup\n");
			return false;
		}
		StartupConfig & config = g_used_startup_config;
		
#ifdef ICK_WINDOWS
		if(config.do_timeBeginPeriod){
			if (timeEndPeriod(1)){
				ICK_LOG_ERROR("timeEndPeriod failed\n");
				return false;
			}
		}
#endif

		if(config.memory_debug){
			DebugAllocator * debug_allocator = static_debug_allocator();
			
			if (debug_allocator->info_list_num() > 0){
				ick::String dump = debug_allocator->Dump();
				ICK_LOG_ERROR("memory leak:\n%s", dump.cstr());
			}else{
				ICK_LOG_INFO("no memory leak\n");
			}
			
			set_static_allocator(debug_allocator->allocator());
			ICK_DELETE(debug_allocator);
		}
		
		if(!config.allocator){
			delete static_allocator();
		}
		set_static_allocator(NULL);
		
		g_startedup = false;
		g_startup_config = ick::StartupConfig();
		return true;
	}
}
