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
#include "base/macro.h"
#include "base/allocator.h"
#include "base/memory.h"
#include "base/cstr.h"
#include "base/crt.h"
#include "base/log.h"
#include "base/abort.h"
#include "base/assert.h"
#include "base/linked_list.h"

namespace ick{
	struct StartupInfo {
		Allocator * allocator;
	};
	bool Startup(const struct StartupInfo & info);
	bool IsStartedup();
	bool Shutdown();
}