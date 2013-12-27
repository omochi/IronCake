#pragma once

namespace ick{
	class Allocator;
	
	struct MutexImpl;
	class Mutex{
	private:
		Allocator * allocator_;
		MutexImpl * impl_;
		
		void Init();
	public:
		Mutex();
		Mutex(Allocator * allocator);
		virtual ~Mutex();
		
		void Lock();
		void Unlock();
		
		void Wait();
		void Notify();//All
	};
}

