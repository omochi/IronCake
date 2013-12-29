#include "wait.h"

#include "error.h"

namespace ick{
#ifdef ICK_WINDOWS
	int WindowsWaitResultGetObjectIndex(DWORD result, int num){
		if (WAIT_OBJECT_0 <= result && result < WAIT_OBJECT_0 + num){
			return result - WAIT_OBJECT_0;
		}
		return -1;
	}
	int WindowsWaitResultGetAbandonedIndex(DWORD result, int num){
		if (WAIT_ABANDONED_0 <= result && result < WAIT_ABANDONED_0 + num){
			return result - WAIT_ABANDONED_0;
		}
		return -1;
	}
	String WindowsWaitResultGetDescription(DWORD result, int num){
		String text;
		switch (result){
		case WAIT_IO_COMPLETION:
			text = String("WAIT_IO_COMPLETION");
			break;
		case WAIT_TIMEOUT:
			text = String("WAIT_TIMEOUT");
			break;
		case WAIT_FAILED:
			text = String::Format("WAIT_FAILED: %s", WindowsLastErrorGetDescription().cstr());
			break;
		default:
			int object_index = WindowsWaitResultGetObjectIndex(result, num);
			if (object_index != -1){
				text = String::Format("WAIT_OBJECT_%d", object_index);
				break;
			}
			int abandoned_index = WindowsWaitResultGetAbandonedIndex(result, num);
			if (abandoned_index != -1){
				text = String::Format("WAIT_ABANDONED_%d", abandoned_index);
				break;
			}

			text = String("0x%08x", result);
		}
		return text;
	}
#endif
}