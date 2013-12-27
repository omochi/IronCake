#pragma once

#include "mutex.h"

namespace ick{
	class ScopedLock {
	private:
		Mutex & mutex_;
	public:
		ScopedLock(Mutex & mutex);
		virtual ~ScopedLock();
	};
}
