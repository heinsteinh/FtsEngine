#!/bin/sh

echo '########################################################'
echo 'Build This Application'
echo '########################################################'
echo ' '


mkdir -p build/build.unix
mkdir -p build/build.macosx
mkdir -p build/build.windows
mkdir -p build/build.ios
mkdir -p build/build.android


cd build
cd build.windows


cmake -G"Visual Studio 12 2013 Win64" ../../   -DCMAKE_BUILD_TYPE=Debug


read -p "Press [Enter] key to End backup..."