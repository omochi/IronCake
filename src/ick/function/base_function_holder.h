// This file was GENERATED by command:
//     pump.py base_function_holder.h.pump
// DO NOT EDIT BY HAND!!!

#pragma once

#include "../base/memory.h"

namespace ick {
	template <typename F> class BaseFunctionHolder;

	template <typename R>
	class BaseFunctionHolder<R(*)()> {
	public:
		typedef R (*FunctionType)();
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() () = 0;
	};

	template <typename R, typename A1>
	class BaseFunctionHolder<R(*)(A1)> {
	public:
		typedef R (*FunctionType)(A1);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1) = 0;
	};

	template <typename R, typename A1, typename A2>
	class BaseFunctionHolder<R(*)(A1, A2)> {
	public:
		typedef R (*FunctionType)(A1, A2);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2) = 0;
	};

	template <typename R, typename A1, typename A2, typename A3>
	class BaseFunctionHolder<R(*)(A1, A2, A3)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3) = 0;
	};

	template <typename R, typename A1, typename A2, typename A3, typename A4>
	class BaseFunctionHolder<R(*)(A1, A2, A3, A4)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4) = 0;
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5>
	class BaseFunctionHolder<R(*)(A1, A2, A3, A4, A5)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) = 0;
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5, typename A6>
	class BaseFunctionHolder<R(*)(A1, A2, A3, A4, A5, A6)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) = 0;
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5, typename A6, typename A7>
	class BaseFunctionHolder<R(*)(A1, A2, A3, A4, A5, A6, A7)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6, A7);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) = 0;
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5, typename A6, typename A7, typename A8>
	class BaseFunctionHolder<R(*)(A1, A2, A3, A4, A5, A6, A7, A8)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6, A7, A8);
		typedef BaseFunctionHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctionHolder(){};
		virtual ThisType * Clone() const = 0;
  virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
      A8 a8) = 0;
	};

}

