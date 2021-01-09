#!/bin/bash

PROJECT_DIR=$(pwd)

cd ..
cd emsdk

echo -e "\e[33mSetting up Emscripten\e[0m"
./emsdk activate latest &>/dev/null
source ./emsdk_env.sh &>/dev/null

echo -e "\e[33mCreating Directories and moving there\e[0m"
cd $PROJECT_DIR
mkdir -p build
mkdir -p assets
cd build

echo -e "\e[33mMaking module\e[0m"
emcmake cmake ..
emmake make

echo -e "\e[33mCopying results\e[0m"
mkdir -p ../app/module
cp ./module/CppWebExploration.js ../app/module/CppWebExploration.js
cp ./module/CppWebExploration.wasm ../app/module/CppWebExploration.wasm