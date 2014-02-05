#pragma once

#include "function.h"

#define ICK_FUNCTION(R,...) ick::Function<R (*)(__VA_ARGS__)>

