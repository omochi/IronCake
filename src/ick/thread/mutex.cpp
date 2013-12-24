#include "mutex.h"

#include "../base/memory.h"
#include "../base/error.h"

#include <pthread.h>

namespace ick{
	struct MutexImpl{
		pthread_mutex_t mutex;
		pthread_cond_t cond;
	};
	
	Mutex::Mutex(){
		impl_ = ICK_NEW(MutexImpl);
		
		impl_->mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
		impl_->cond = PTHREAD_COND_INITIALIZER;
	}
	Mutex::~Mutex(){
		ICK_EN_CALL(pthread_cond_destroy(&impl_->cond));
		ICK_EN_CALL(pthread_mutex_destroy(&impl_->mutex));
		ICK_DELETE(impl_);
	}
	
	void Mutex::Lock(){
		ICK_EN_CALL(pthread_mutex_lock(&impl_->mutex));
	}
	
	void Mutex::Unlock(){
		ICK_EN_CALL(pthread_mutex_unlock(&impl_->mutex));
	}
	
	void Mutex::Wait(){
		ICK_EN_CALL(pthread_cond_wait(&impl_->cond, &impl_->mutex));
	}
	
	void Mutex::Notify(){
		ICK_EN_CALL(pthread_cond_broadcast(&impl_->cond));
	}
}
