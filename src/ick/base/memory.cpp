//
//  memory.cpp
//  IronCake
//
//  Created by おもちメタル on 2013/12/03.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include "memory.h"

namespace ick{
	void * Offset(void * address, int offset){
		return (void *)((intptr_t)address + offset);
	}
	void * Align(void * address, size_t alignment){
		uintptr_t x = (uintptr_t)address;
		uintptr_t a = (uintptr_t)alignment;
		return (void *)( (x+a-1) & ~(a-1) );
	}
	
	void Copy(const void * src, void * dest, size_t size){
		const uint8_t * sp = static_cast<const uint8_t *>(src);
		uint8_t * dp = static_cast<uint8_t *>(dest);
		for(int i = 0; i < (int)size; i++){
			dp[0] = sp[0];
			dp++;
			sp++;
		}
	}
	
	void Write32(void * address, uint32_t value){
		*(uint8_t *)Offset(address, 0) = ( value & 0xFF000000 ) >> 24;
		*(uint8_t *)Offset(address, 1) = ( value & 0x00FF0000 ) >> 16;
		*(uint8_t *)Offset(address, 2) = ( value & 0x0000FF00 ) >> 8;
		*(uint8_t *)Offset(address, 3) = ( value & 0x000000FF ) ;
	}
	uint32_t Read32(void * address){
		return
		*(uint8_t *)Offset(address, 0) << 24 |
		*(uint8_t *)Offset(address, 1) << 16 |
		*(uint8_t *)Offset(address, 2) << 8 |
		*(uint8_t *)Offset(address, 3) ;
	}

}