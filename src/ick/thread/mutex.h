#pragma once



namespace ick{
	struct MutexImpl;
	class Mutex{
	private:
		MutexImpl * impl_;
	public:
		Mutex();
		virtual ~Mutex();
		
		void Lock();
		void Unlock();
		
		void Wait();
		void Notify();//All
	};
}

