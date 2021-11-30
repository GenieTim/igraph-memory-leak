#!/usr/bin/env bash

cd "$(dirname "$0")/.." || exit 10
ROOT_DIR=$(pwd)

mkdir -p build
cd build || exit 5
cmake .. || exit 1
cmake --build . || exit 9
ASAN_OPTIONS=detect_leaks=1 ./leak_test || exit 6 # -s --durations yes 
