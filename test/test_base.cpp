#include "test_base.h"


void TestBase::SetUp(){
	struct ick::StartupInfo info = { NULL, true };
	ick::Startup(info);
}
void TestBase::TearDown(){
	if (ick::static_debug_allocator()->info_list()->num() > 0){
		ick::String dump = ick::static_debug_allocator()->Dump();
		FAIL() << dump.cstr();
	}
	ick::Shutdown();
}

