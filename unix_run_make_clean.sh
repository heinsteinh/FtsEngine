#!/bin/sh

./clean.sh

echo '########################################################'
echo 'Build This Application'
echo '########################################################'
echo ' '

mkdir -p build/unix
mkdir -p build/macosx
mkdir -p build/windows

cd build
cd unix

cmake -G"Unix Makefiles" ../../ -DCMAKE_BUILD_TYPE=Debug

make

cd ../../

cd bin

cd unix

echo ' '
echo 'Executing the Debug'
echo ' '


./ProjectBuilder
