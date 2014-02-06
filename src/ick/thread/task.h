#pragma once

#include "../function/function.h"
#include "../function/function_macro.h"

namespace ick{
	// 返り値: なし
	// 引数1: cancelled
	typedef ICK_FUNCTION(void, bool) Task;
	
	// その後解放する
	void TaskRun(Task * task);
	void TaskCancel(Task * task);
	
	// newのラッパー
	Task * TaskCreate(ICK_FUNCTION(void, bool) func);
	
	// キャンセル引数が無いファンクションから自動生成する
	// キャンセルの場合に何もしないものと、
	// キャンセルだろうが実行するものがある
	Task * TaskCreate(ICK_FUNCTION(void) func, bool skip_on_cancelled);
}
