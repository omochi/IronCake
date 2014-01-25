#!/bin/bash
set -ueo pipefail
script_dir=$(cd "$(dirname "$0")"; pwd)
cd "$script_dir/IronCakeSample/src/main"
ndk-build "$@"
