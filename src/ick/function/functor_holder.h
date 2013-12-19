// This file was GENERATED by command:
//     pump.py functor_holder.h.pump
// DO NOT EDIT BY HAND!!!

#pragma once

#include "../base/memory.h"

namespace ick {
	template <typename FP> class BaseFunctorHolder;
	template <typename F, typename FP> class FunctorHolder;

	template <typename R>
	class BaseFunctorHolder<R(*)()> {
	public:
		typedef R (*FunctionType)();
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() () = 0;
	};

	template <typename F, typename R>
	class FunctorHolder<F, R(*)()> :
	public BaseFunctorHolder<R(*)()> {
	public:
		typedef R (*FunctionType)();
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() () {
			return functor_();
		}
	};

	template <typename R, typename A1>
	class BaseFunctorHolder<R(*)(A1)> {
	public:
		typedef R (*FunctionType)(A1);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1) = 0;
	};

	template <typename F, typename R, typename A1>
	class FunctorHolder<F, R(*)(A1)> :
	public BaseFunctorHolder<R(*)(A1)> {
	public:
		typedef R (*FunctionType)(A1);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1) {
			return functor_(a1);
		}
	};

	template <typename R, typename A1, typename A2>
	class BaseFunctorHolder<R(*)(A1, A2)> {
	public:
		typedef R (*FunctionType)(A1, A2);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2) = 0;
	};

	template <typename F, typename R, typename A1, typename A2>
	class FunctorHolder<F, R(*)(A1, A2)> :
	public BaseFunctorHolder<R(*)(A1, A2)> {
	public:
		typedef R (*FunctionType)(A1, A2);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1, A2 a2) {
			return functor_(a1, a2);
		}
	};

	template <typename R, typename A1, typename A2, typename A3>
	class BaseFunctorHolder<R(*)(A1, A2, A3)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3) = 0;
	};

	template <typename F, typename R, typename A1, typename A2, typename A3>
	class FunctorHolder<F, R(*)(A1, A2, A3)> :
	public BaseFunctorHolder<R(*)(A1, A2, A3)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1, A2 a2, A3 a3) {
			return functor_(a1, a2, a3);
		}
	};

	template <typename R, typename A1, typename A2, typename A3, typename A4>
	class BaseFunctorHolder<R(*)(A1, A2, A3, A4)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4) = 0;
	};

 template <typename F, typename R, typename A1, typename A2, typename A3,
     typename A4>
	class FunctorHolder<F, R(*)(A1, A2, A3, A4)> :
	public BaseFunctorHolder<R(*)(A1, A2, A3, A4)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4) {
			return functor_(a1, a2, a3, a4);
		}
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5>
	class BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) = 0;
	};

 template <typename F, typename R, typename A1, typename A2, typename A3,
     typename A4, typename A5>
	class FunctorHolder<F, R(*)(A1, A2, A3, A4, A5)> :
	public BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
			return functor_(a1, a2, a3, a4, a5);
		}
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5, typename A6>
	class BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5, A6)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) = 0;
	};

 template <typename F, typename R, typename A1, typename A2, typename A3,
     typename A4, typename A5, typename A6>
	class FunctorHolder<F, R(*)(A1, A2, A3, A4, A5, A6)> :
	public BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5, A6)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
			return functor_(a1, a2, a3, a4, a5, a6);
		}
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5, typename A6, typename A7>
	class BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5, A6, A7)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6, A7);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) = 0;
	};

 template <typename F, typename R, typename A1, typename A2, typename A3,
     typename A4, typename A5, typename A6, typename A7>
	class FunctorHolder<F, R(*)(A1, A2, A3, A4, A5, A6, A7)> :
	public BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5, A6, A7)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6, A7);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
		virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) {
			return functor_(a1, a2, a3, a4, a5, a6, a7);
		}
	};

 template <typename R, typename A1, typename A2, typename A3, typename A4,
     typename A5, typename A6, typename A7, typename A8>
	class BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5, A6, A7, A8)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6, A7, A8);
		typedef BaseFunctorHolder<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);
	public:
		virtual ~BaseFunctorHolder(){};
		virtual ThisType * Clone() const = 0;
  virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
      A8 a8) = 0;
	};

 template <typename F, typename R, typename A1, typename A2, typename A3,
     typename A4, typename A5, typename A6, typename A7, typename A8>
	class FunctorHolder<F, R(*)(A1, A2, A3, A4, A5, A6, A7, A8)> :
	public BaseFunctorHolder<R(*)(A1, A2, A3, A4, A5, A6, A7, A8)> {
	public:
		typedef R (*FunctionType)(A1, A2, A3, A4, A5, A6, A7, A8);
		typedef BaseFunctorHolder<FunctionType> SuperType;
		typedef FunctorHolder<F, FunctionType> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const { return ICK_NEW(ThisType, functor_); }
  virtual R operator() (A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7,
      A8 a8) {
			return functor_(a1, a2, a3, a4, a5, a6, a7, a8);
		}
	};


}
