#pragma once

#include "../base/string.h"
#include "runnable.h"

namespace ick{
	struct ThreadImpl;
	class Thread : public Runnable{
	private:
		ThreadImpl * impl_;
		bool running_;
		String name_;
	public:
		Thread();
		virtual ~Thread();
		
		bool running() const;
		String name() const;
		//	Startまでにする事
		void set_name(const String & name);

		void Start();
		void Join();
	};
	
}