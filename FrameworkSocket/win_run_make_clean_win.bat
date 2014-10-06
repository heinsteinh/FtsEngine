#!/bin/sh

./clean.sh


echo ######################################################## Start

set START_TIME=%time%
echo ########################################################
echo Build This Application
echo ########################################################
echo 


mkdir -p build/build.unix
mkdir -p build/build.macosx
mkdir -p build/build.windows
mkdir -p build/build.ios
mkdir -p build/build.android


cd build
cd build.windows


echo ****** 
cmake -G"Visual Studio 12 2013 Win64" ../../   -DCMAKE_BUILD_TYPE=Debug


echo ******
"C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe"   ALL_BUILD.vcxproj  /property:Configuration=Debug
"C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe"   ALL_BUILD.vcxproj  /property:Configuration=Release


cd ../../

cd bin

cd Debug 

echo Executing the Debug

ProjectBuilder.exe

echo ######################################################## END
 
echo Start Time: %START_TIME%
echo End Time: %TIME%

pause