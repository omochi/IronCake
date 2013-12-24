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
	
}