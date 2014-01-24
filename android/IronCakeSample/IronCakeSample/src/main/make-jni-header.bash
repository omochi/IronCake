#!/bin/bash
set -ueo pipefail
script_dir=$(cd "$(dirname "$0")"; pwd)

javah \
    -d $script_dir/jni \
    -classpath \
$ANDROID_SDK_HOME/platforms/android-19/android.jar:\
$script_dir/../../../IronCake/build/classes/debug:\
$script_dir/../../build/classes/debug\
    "$@"
  