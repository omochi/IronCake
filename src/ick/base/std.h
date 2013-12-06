//
//  type.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/05.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

#include "platform.h"
#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

#ifndef va_copy
#	define va_copy(dest, src) (dest = src)
#endif
