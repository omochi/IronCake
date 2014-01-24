#include "test_base.h"

void TestBase::SetUp(){
	ick::g_startup_config.allocator = new ick::DebugAllocator(new ick::MallocAllocator());
	ick::Startup();
}
void TestBase::TearDown(){
	ick::DebugAllocator * debug_allocator = ick::static_debug_allocator();
	if (debug_allocator->info_list_num() > 0){
		ick::String dump = debug_allocator->Dump();
		FAIL() << dump.cstr();
	}
	ick::Shutdown();
	
	ick::MallocAllocator * malloc_allocator = static_cast<ick::MallocAllocator *>(debug_allocator->allocator());
	delete debug_allocator;
	delete malloc_allocator;
}

