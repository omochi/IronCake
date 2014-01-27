//
//  math.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/07.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

namespace ick{
	template <typename T> T Min(const T & a, const T & b);
	template <typename T> T Max(const T & a, const T & b);
	template <typename T> T Clamp(const T & x, const T & min, const T & max);
	
	
	template <typename T> T Min(const T & a, const T & b){
		return a < b ? a: b;
	}
	template <typename T> T Max(const T & a, const T & b){
		return a > b ? a: b;
	}
	template <typename T> T Clamp(const T & x, const T & min, const T & max){
		return x < min ? min: ( max < x ? max: x );
	}
}
