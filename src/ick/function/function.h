#pragma once

#include "../base/memory.h"

namespace ick {
	
	
	
	template <typename FP> class Function;
	
	template <typename FP> class FunctorTrait;
	
	template <typename FP> class BaseFunctorHolder;
	template <typename F, typename FP> class FunctorHolder;
	
	
	
//	template <typename R>
//	class FunctorTrait<R(*)()> {
//	public:
//		typedef R (*FunctionType)();
//		typedef R ReturnType;
//	};
//	template <typename R, typename A1>
//	class FunctorTrait<R(*)(A1)> {
//	public:
//		typedef R (*FunctionType)(A1);
//		typedef R ReturnType;
//		typedef A1 Arg1Type;
//	};
	
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
	
	template <typename F, typename R>
	class FunctorHolder<F, R(*)()> : public BaseFunctorHolder<R(*)()> {
	public:
		typedef BaseFunctorHolder<R(*)()> SuperType;
		typedef FunctorHolder<F, R(*)()> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const {
			return ICK_NEW(ThisType, functor_);
		}
		virtual R operator() () { return functor_(); }
	};

	template <typename F, typename R, typename A1>
	class FunctorHolder<F, R(*)(A1)> : public BaseFunctorHolder<R(*)(A1)> {
	public:
		typedef BaseFunctorHolder<R(*)(A1)> SuperType;
		typedef FunctorHolder<F, R(*)(A1)> ThisType;
	private:
		F functor_;
	public:
		FunctorHolder(F functor):functor_(functor){}
		SuperType * Clone() const {
			return ICK_NEW(ThisType, functor_);
		}
		virtual R operator() (A1 a1) { return functor_(a1); }
	};

	template <typename R>
	class Function<R(*)()> {
	public:
		typedef R (*FunctionType)();
		typedef R ReturnType;
		typedef Function<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);

		BaseFunctorHolder<R(*)()> * holder_;
	public:
		Function(FunctionType native_function){
			holder_ = ICK_NEW(FunctorHolder<FunctionType ICK_COMMA FunctionType>, native_function);
		}
		template <typename F>
		Function(const FunctorHolder<F, FunctionType> & functor_holder){
			holder_ = ICK_NEW(FunctorHolder<F ICK_COMMA FunctionType>, functor_holder);
		}
		Function(const ThisType & copy){
			holder_ = copy.holder_->Clone();
		}
		virtual ~Function(){
			ICK_DELETE(holder_);
		}
		R operator() () { return (*holder_)(); }
	};
	
	template <typename R, typename A1>
	class Function<R(*)(A1)>{
	public:
		typedef R (*FunctionType)(A1);
		typedef R ReturnType;
		typedef A1 Arg1Type;
		typedef Function<FunctionType> ThisType;
	private:
		ThisType & operator = (const ThisType & copy);

		BaseFunctorHolder<FunctionType> * holder_;
	public:
		//暗黙
		Function(FunctionType native_function){
			holder_ = ICK_NEW(FunctorHolder<FunctionType ICK_COMMA FunctionType>, native_function);
		}
		template <typename F>
		Function(const FunctorHolder<F, FunctionType> & functor_holder){
			holder_ = ICK_NEW(FunctorHolder<F ICK_COMMA FunctionType>, functor_holder);
		}
		Function(const ThisType & copy){
			holder_ = copy.holder_->Clone();
		}
		virtual ~Function(){
			ICK_DELETE(holder_);
		}
		R operator() (A1 a1) { return (*holder_)(a1); }
	};
	
	template <typename FP, int N> class FunctionBinder;
	
	template <typename R, typename A1>
	class FunctionBinder<R(*)(A1),1> {
	private:
		Function<R(*)(A1)> function_;
		A1 a1_;
	public:
		FunctionBinder(Function<R(*)(A1)> function, A1 a1):
		function_(function),a1_(a1){
		}
		R operator() () { return function_(a1_); }
	};
	

	template <typename R,typename A1>
	Function<R(*)()> FunctionBind1(Function<R(*)(A1)> function,A1 a1){
		return Function<R(*)()>(FunctorHolder<FunctionBinder<R(*)(A1), 1>, R(*)()>(FunctionBinder<R(*)(A1), 1>(function, a1) ));
	}
	
	template <typename R, typename A1>
	Function<R(*)()> FunctionBind1(R (*function)(A1), A1 a1){
		return FunctionBind1(Function<R(*)(A1)>(function), a1);
	}
	
	
	
}