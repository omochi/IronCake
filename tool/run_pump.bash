#!/bin/bash
set -ueo pipefail
script_dir=$(cd $(dirname "$0");pwd)
source_dir="$(dirname "$script_dir")/src"
pump_path="$script_dir/pump.py"
source_files=(
	"$source_dir/ick/function/base_function_holder.h.pump"
	"$source_dir/ick/function/native_function_holder.h.pump"
	"$source_dir/ick/function/function_holder.h.pump"
	"$source_dir/ick/function/function.h.pump"
	"$source_dir/ick/function/function_binder.h.pump"
	"$source_dir/ick/function/method_binder.h.pump"
	"$source_dir/ick/function/function_bind_decl.h.pump"
	"$source_dir/ick/function/function_bind.h.pump"
	)
main(){
	for source in ${source_files[@]} ; do
		echo "$source"
		$pump_path "$source"
	done
	return 0
}
main "$@"
exit $?