#pragma once

namespace ick {
	
	template <typename F> class Function;
	
	template <typename R>
	class Function<R(*)()> {
	public:
		typedef R TypeR;
		typedef R (*FunctionType)();
		virtual ~Function(){}
		virtual R operator() () = 0;
	};
	template <typename R, typename A1>
	class Function<R(*)(A1)> {
	public:
		typedef R TypeR;
		typedef A1 TypeA1;
		typedef R (*FunctionType)(A1);
		virtual ~Function(){}
		virtual R operator() (A1 a1) = 0;
	};
	template <typename R, typename A1, typename A2>
	class Function<R(*)(A1,A2)>{
	public:
		typedef R TypeR;
		typedef A1 TypeA1;
		typedef A2 TypeA2;
		typedef R (*FunctionType)(A1,A2);
		virtual ~Function(){}
		virtual R operator() (A1 a1, A2 a2) = 0;
	};
	
	//ネイティブ関数をFunctionにするためのクラス
	//暗黙型変換コンストラクタでの利用を想定
	template <typename F> class NativeFunction;
	
	template <typename R>
	class NativeFunction<R(*)()> : public Function<R(*)()>{
	public:
		typedef R (*FunctionType)();
	private:
		FunctionType function_;
	public:
		NativeFunction(FunctionType function):
		function_(function)
		{}
		virtual R operator() () { return function_(); }
	};
	
	template <typename R, typename A1>
	class NativeFunction<R(*)(A1)> : public Function<R(*)(A1)>{
	public:
		typedef R (*FunctionType)(A1);
	private:
		FunctionType function_;
	public:
		NativeFunction(FunctionType function):
		function_(function)
		{}
		virtual R operator() (A1 a1) { return function_(a1); }
	};
	
	template <typename R, typename A1, typename A2>
	class NativeFunction<R(*)(A1,A2)> : public Function<R(*)(A1,A2)>{
	public:
		typedef R (*FunctionType)(A1,A2);
	private:
		FunctionType function_;
	public:
		NativeFunction(FunctionType function):
		function_(function)
		{}
		virtual R operator() (A1 a1, A2 a2) { return function_(a1,a2); }
	};
	
	
	template <typename F, typename FT, int N> class FunctionBinder;
	
	template <typename F, typename R, typename A1>
	class FunctionBinder<F, R(*)(A1), 1> : public Function<R(*)()> {
	private:
		F function_;
		A1 a1_;
	public:
		FunctionBinder(F function, A1 a1):
		function_(function),
		a1_(a1)
		{}
		virtual R operator() () { return function_(a1_); }
	};
	
	template <typename F, typename R, typename A1, typename A2>
	class FunctionBinder<F, R(*)(A1,A2), 1> : public Function<R(*)(A2)> {
	private:
		F function_;
		A1 a1_;
	public:
		FunctionBinder(F function, A1 a1):
		function_(function),
		a1_(a1)
		{}
		virtual R operator() (A2 a2) { return function_(a1_, a2); }
	};
	
	template <typename F>
	FunctionBinder<F, typename F::FunctionType, 1>
	FunctionBind(F function, typename F::TypeA1 a1){
		return FunctionBinder<F,typename F::FunctionType, 1>(function, a1);
	}

}