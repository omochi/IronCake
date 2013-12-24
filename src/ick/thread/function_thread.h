#pragma once

#include "thread.h"
#include "../function/function.h"

namespace ick{
	class FunctionThread : public Thread {
	private:
		Function<void (*)()> function_;
	public:
		FunctionThread(Function<void (*)()> function):
		function_(function){
		}
		virtual ~FunctionThread(){
		}
		virtual void Run(){
			function_();
		}
	};
}