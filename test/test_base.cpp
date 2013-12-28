#include "test_base.h"


void TestBase::SetUp(){
	ick::g_startup_config.memory_debug = true;
	ick::Startup();
}
void TestBase::TearDown(){
	if (ick::static_debug_allocator()->info_list()->num() > 0){
		ick::String dump = ick::static_debug_allocator()->Dump();
		FAIL() << dump.cstr();
	}
	ick::Shutdown();
}

