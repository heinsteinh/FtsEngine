#!/bin/sh




# For benefit of log files.
echo pwd = `pwd`
echo $0 $*
# Make sure bash fails completely if any command fails
set -e




echo '########################################################'
echo 'Build This Application for MAC OS'
echo '########################################################'
echo ' '

mkdir -p build/build.unix
mkdir -p build/build.macosx
mkdir -p build/build.windows
mkdir -p build/build.ios
mkdir -p build/build.android


cd build
cd build.unix


cmake -G"Unix Makefiles" ../../ -DCMAKE_BUILD_TYPE=Debug

make

cd ../../

cd bin

cd unix


echo ' '
echo 'Executing the Debug'
echo ' '


./ProjectBuilder
