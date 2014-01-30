#pragma once

#include "../function/function.h"

namespace ick{
	class TaskPostable {
	public:
		virtual ~TaskPostable(){};
		
		virtual void PostTask(const Function<void (*)()> & task) = 0;
	};
}
