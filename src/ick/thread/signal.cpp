#include "signal.h"

#include "../base/memory.h"
#include "mutex.h"
#include "scoped_lock.h"

namespace ick{
	Signal::Signal(){
		mutex_ = ICK_NEW(Mutex);
		on_ = false;
	}
	Signal::~Signal(){
		ICK_DELETE(mutex_);
	}

	bool Signal::on() const{
		ICK_SCOPED_LOCK(*mutex_);
		return on_;
	}
	void Signal::set_on(bool on){
		ICK_SCOPED_LOCK(*mutex_);
		on_ = on;
		mutex_->Broadcast();
	}
	
	void Signal::Wait(){
		ICK_SCOPED_LOCK(*mutex_);
		while(!on_){ mutex_->Wait(); }
	}
}