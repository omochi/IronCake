#pragma once

namespace ick{
	void Sleep(double time);
	
	//windows用
	void ClockInit();
	void ClockFinal();

	//windowsでは50日で0に戻る
	double ClockGet();
}

