#!/bin/bash
set -ueo pipefail
main(){
	find "$@" \
		-name "*.h" -o \
		-name "*.cpp"
	return 0
}
main "$@"
exit $?