// This file was GENERATED by command:
//     pump.py function_bind_decl.h.pump
// DO NOT EDIT BY HAND!!!

#pragma once

namespace ick {
	template <typename FP, int N> class FunctionBinder;


	template <typename R, typename A1>
	Function<R(*)()>
	FunctionBind1(Function<R(*)(A1),1> function
	, A1 a1){
		return Function<R(*)()>(
			FunctorHolder<
				FunctionBinder<R(*)(A1),1>,
				R(*)(A1)
			>(
				FunctionBinder<R(*)(A1),1>(
					*function.holder() , a1_
				)
			)
		);
	}


	template <typename R, typename A1, typename A2>
	Function<R(*)(A2)>
	FunctionBind1(Function<R(*)(A1, A2),1> function
	, A1 a1){
		return Function<R(*)(A2)>(
			FunctorHolder<
				FunctionBinder<R(*)(A1, A2),1>,
				R(*)(A1, A2)
			>(
				FunctionBinder<R(*)(A1, A2),1>(
					*function.holder() , a1_
				)
			)
		);
	}


	template <typename R, typename A1, typename A2>
	Function<R(*)()>
	FunctionBind1(Function<R(*)(A1, A2),2> function
	, A1 a1, A2 a2){
		return Function<R(*)()>(
			FunctorHolder<
				FunctionBinder<R(*)(A1, A2),2>,
				R(*)(A1, A2)
			>(
				FunctionBinder<R(*)(A1, A2),2>(
					*function.holder() , a1_, a2_
				)
			)
		);
	}


}
