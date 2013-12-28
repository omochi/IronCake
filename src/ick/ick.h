//
//  ick.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/04.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "base/platform.h"
#include "base/compiler.h"
#include "base/std.h"
#include "base/build.h"
#include "base/macro.h"
#include "base/allocator.h"
#include "base/debug_allocator.h"
#include "base/memory.h"
#include "base/cstr.h"
#include "base/crt.h"
#include "base/log.h"
#include "base/abort.h"
#include "base/assert.h"
#include "base/linked_list.h"
#include "base/array.h"
#include "base/string.h"
#include "base/error.h"
#include "base/time.h"

#include "function/functor_holder.h"
#include "function/function.h"
#include "function/function_bind.h"

#include "thread/mutex.h"
#include "thread/scoped_lock.h"
#include "thread/runnable.h"
#include "thread/thread.h"
#include "thread/function_thread.h"
#include "thread/loop_thread.h"

#ifdef ICK_WINDOWS
#	include "windows/tchar.h"
#	include "windows/error.h"
#	include "windows/wait.h"
#endif

#include "app/application_delegate.h"
#include "app/application.h"

namespace ick{
	struct StartupConfig {
		Allocator * allocator;
		bool memory_debug;
	};
	//デフォルト値で初期化済み
	extern struct StartupConfig g_startup_config;
	bool Startup();
	bool IsStartedup();
	bool Shutdown();
}