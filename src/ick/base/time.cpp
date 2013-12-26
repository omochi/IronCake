#include "time.h"

#include "../base/platform.h"
#include "../base/error.h"

#include <math.h>

#ifdef ICK_WINDOWS
#	include <Windows.h>
#else
#	include <sys/time.h>
#	include <time.h>
#endif

namespace ick{
	void Sleep(double time){
#ifdef ICK_WINDOWS
		::Sleep(static_cast<DWORD>(round(time * 1000.0)));
#else
		double time_sec = floor(time);
		double time_nano = floor((time - time_sec) * 1000000000.0);
		timespec ts;
		ts.tv_sec = static_cast<time_t>(time_sec);
		ts.tv_nsec = static_cast<long>(time_nano);
		int ret = nanosleep(&ts, NULL);
		if(ret){
			//シグナル割り込みの場合だが・・・？
			ICK_EN_ABORT(errno, "nanosleep");
		}
#endif
	}
	
	double ClockGet(){
		timeval tv;
		if(gettimeofday(&tv, NULL)){
			ICK_EN_ABORT(errno, "gettiemofday");
		}
		double clock = static_cast<double>(tv.tv_sec) +
		static_cast<double>(tv.tv_usec) / 1000000000.0;
		return clock;
	}
}
