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

#ifdef ICK_WINDOWS
#	include "windows/tchar.h"
#	include "windows/error.h"
#endif

namespace ick{
	struct StartupInfo {
		Allocator * allocator;
		bool memory_debug;
	};
	bool Startup(const struct StartupInfo & info);
	bool IsStartedup();
	bool Shutdown();
}