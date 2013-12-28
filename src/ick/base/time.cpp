#include "time.h"

#include "../base/platform.h"
#include "../base/error.h"

#include <math.h>

#ifdef ICK_WINDOWS
#	include <Windows.h>
#	include <mmsystem.h>
#	pragma comment(lib, "winmm.lib")
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

	void ClockInit(){
#ifdef ICK_WINDOWS
		if (timeBeginPeriod(1)){
			ICK_ABORT("timeBeginPeriod");
		}
#endif
	}
	void ClockFinal(){
#ifdef ICK_WINDOWS
		if (timeEndPeriod(1)){
			ICK_ABORT("timeEndPeriod");
		}
#endif
	}
	
	double ClockGet(){
#ifdef ICK_WINDOWS
		DWORD time = timeGetTime();
		return static_cast<double>(time) / 1000.0;
#else
		timeval tv;
		if(gettimeofday(&tv, NULL)){
			ICK_EN_ABORT(errno, "gettiemofday");
		}
		double clock = static_cast<double>(tv.tv_sec) +
		static_cast<double>(tv.tv_usec) / 1000000000.0;
		return clock;
#endif
	}
}
