//
//  GLTestApp.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/29.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include <ick/ick.h>

class SampleAppController : public ick::ApplicationController {
	int sec_frame_count_;
	double prev_sec_clock_;
	int frame_count_;
public:
	virtual ~SampleAppController();
	virtual void ApplicationDidLaunch();
	virtual void ApplicationWillTerminate();
	virtual void ApplicationOnUpdate();
	virtual void ApplicationOnRender();
};
