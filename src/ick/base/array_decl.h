//
//  array_decl.h
//  IronCake
//
//  Created by おもちメタル on 2013/12/07.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#pragma once

namespace ick{
	template <typename T> class Array;
	
	template <typename T> Array<T> ArrayMake1(const T & a1);
	template <typename T> Array<T> ArrayMake2(const T & a1,const T & a2);
	template <typename T> Array<T> ArrayMake3(const T & a1,const T & a2,const T & a3);
	template <typename T> Array<T> ArrayMake4(const T & a1,const T & a2,const T & a3,const T & a4);
	template <typename T> Array<T> ArrayMake5(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5);
	template <typename T> Array<T> ArrayMake6(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5,const T & a6);
	template <typename T> Array<T> ArrayMake7(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5,const T & a6,const T & a7);
	template <typename T> Array<T> ArrayMake8(const T & a1,const T & a2,const T & a3,const T & a4,const T & a5,const T & a6,const T & a7,const T & a8);
}
