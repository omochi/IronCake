#pragma once

namespace ick{
	class Mutex;
	
	class Signal{
	private:
		Mutex * mutex_;
		bool on_;
	public:
		Signal();
		virtual ~Signal();
		
		bool on() const;
		void set_on(bool on);
		
		void Wait();
	};
}
