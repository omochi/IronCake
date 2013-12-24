#pragma once

namespace ick{
	class Runnable {
	public:
		virtual void Run() = 0;
		virtual ~Runnable(){};
	};
}
