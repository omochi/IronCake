#pragma once

#include "assert.h"
#include "memory.h"

namespace ick{
	template <typename T>
	void PropertySet(T * & property, T * value);
	template <typename T>
	void PropertyClear(T * & property);
	template <typename T>
	void PropertySet(T * & property, bool & property_release, T * value, bool release);
	template <typename T>
	void PropertyClear(T * & property, bool & property_release);
	
	//	古い値を解放する
	template <typename T>
	void PropertySet(T * & property, T * value){
		if(property){ ICK_DELETE(property); }
		property = value;
	}
	template <typename T>
	void PropertyClear(T * & property){
		PropertySet<T>(property, NULL);
	}
	
	//	解放するかどうかのフラグも持つ
	template <typename T>
	void PropertySet(T * & property, bool & property_release, T * value, bool release){
		//nullセットする場合はreleaseはfalseである事
		ICK_ASSERT(property || !property_release);
		ICK_ASSERT(value || !release);
		if(property_release){ ICK_DELETE(property); }
		property = value;
		property_release = release;
	}
	
	template <typename T>
	void PropertyClear(T * & property, bool & property_release){
		PropertySet(property, property_release, NULL, false);
	}
}

