#include "scoped_lock.h"

namespace ick{
	ScopedLock::ScopedLock(Mutex & mutex):
	mutex_(mutex){
		mutex_.Lock();
	}
	ScopedLock::~ScopedLock(){
		mutex_.Unlock();
	}
}

