#include "time.h"

#include "../base/platform.h"

#include <math.h>

#ifdef ICK_WINDOWS
#	include <Windows.h>
#else
#	include <time.h>
#endif

namespace ick{
	void Sleep(double time){
#ifdef ICK_WINDOWS
		::Sleep(static_cast<DWORD>(round(time * 1000.0)));
#else
		double time_sec = floor(time);
		double time_nano = floor((time - time_sec) * 1000.0 * 1000.0 * 1000.0);
		timespec ts;
		ts.tv_sec = static_cast<time_t>(time_sec);
		ts.tc_nsec = static_cast<long>(time_nano);
		int ret = nanosleep(&ts, NULL);
		if(ret){
			//シグナル割り込みの場合だが・・・？
			ICK_EN_ABORT(errno, "nanosleep");
		}
#endif
	}
}
