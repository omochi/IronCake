#!/bin/bash
script_dir=$(cd $(dirname "$0"); pwd)
cd "$script_dir"
ndk-build \
	--jobs=8 \
	NDK_PROJECT_PATH=. \
	NDK_APPLICATION_MK=Application.mk \
	"$@"
