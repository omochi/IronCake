#pragma once

#include "task.h"

// 実行部分の実装はインターフェースの実装固有で、
// インターフェースには含まれない

// PostしたTaskの所有権はQueueに移る

// 実装時はTaskの実行とCancelを同期化しなければならない。
// 実行かCancelがされるとTaskは解放される。

// キューの開放時には残っているTaskを全てCancelする。

namespace ick{
	class TaskQueueInterface {
	public:
		virtual ~TaskQueueInterface(){}

		virtual void Post(Task * task) = 0;
		virtual void Cancel(Task * task) = 0;
	};
}
