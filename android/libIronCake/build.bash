#!/bin/bash
script_dir=$(cd $(dirname "$0"); pwd)
cd "$script_dir"
ndk-build NDK_PROJECT_PATH=. NDK_APPLICATION_MK=Application.mk "$@"
