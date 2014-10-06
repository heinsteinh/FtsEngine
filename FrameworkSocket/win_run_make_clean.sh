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

"C:\Program Files (x86)\MSBuild\12.0\Bin\MSBuild.exe"   ALL_BUILD.vcxproj  /property:Configuration=Debug


cd ../../
cd bin
cd Debug 
echo Executing the Debug
ProjectBuilder.exe

echo ########## END


read -p "Press [Enter] key to End backup..."

#./ProjectBuilder.sln