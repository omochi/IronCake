#pragma once

#include "runnable.h"

namespace ick{
	struct ThreadImpl;
	class Thread : public Runnable{
	private:
		ThreadImpl * impl_;
		bool running_;
	public:
		Thread();
		virtual ~Thread();
		
		bool running() const { return running_; }
		
		void Start();
		void Join();
	};
	
	template <typename F> class FunctionThread : public Thread{
	private:
		F function_;
	public:
		FunctionThread(F function):function_(function){}
		virtual void Run(){	function_(); }
		
		F function() const { return function_; }
	};
	
}