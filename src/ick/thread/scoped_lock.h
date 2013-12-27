#pragma once

#include "mutex.h"


#define ICK_SCOPED_LOCK(mutex) ICK__SCOPED_LOCK(mutex, __LINE__ )
#define ICK__SCOPED_LOCK(mutex,line) ICK___SCOPED_LOCK(mutex,line)
#define ICK___SCOPED_LOCK(mutex,line) ick::ScopedLock anonymous_scoped_lock_##line(mutex)

namespace ick{
	class ScopedLock {
	private:
		Mutex & mutex_;
	public:
		ScopedLock(Mutex & mutex);
		virtual ~ScopedLock();
	};
}

