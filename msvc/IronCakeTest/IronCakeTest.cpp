// IronCakeTest.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <gtest/gtest.h>

int _tmain(int argc, _TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	int status = RUN_ALL_TESTS();
	getchar();
	return status;
}

