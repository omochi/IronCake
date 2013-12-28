//
//  GLTestApp.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/29.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include <ick/ick.h>

class GLTestAppController : public ick::ApplicationController {
	
	int sec_frame_count_;
	double prev_sec_clock_;

	
public:
	virtual ~GLTestAppController();
	virtual void ApplicationDidLaunch(ick::Application * application);
	virtual void ApplicationWillTerminate(ick::Application * application);
	virtual void ApplicationOnUpdate(ick::Application * application);
};
