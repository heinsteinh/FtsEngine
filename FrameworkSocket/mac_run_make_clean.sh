#!/bin/sh
# SCRIPT:mac_run_make_clean.sh
#
# AUTHOR: Heinstein
#
# DATE: 09/24/2014

# REV: 1.0.A
#
# PURPOSE:
#


#./clean.sh



echo '########################################################'
echo 'Build This Application for IOS'
echo '########################################################'
echo ' '

mkdir -p build/build.unix
mkdir -p build/build.macosx
mkdir -p build/build.windows
mkdir -p build/build.ios
mkdir -p build/build.android



cd build
cd build.macosx

#cmake -GXcode ../../  -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake -GXcode ../../  -DCMAKE_BUILD_TYPE=Debug

xcodebuild -list


xcodebuild  -configuration Debug clean Build



cd ../../

cd bin

cd macos

cd Debug


echo 'Executing the Debug'


./ProjectBuilder



#export DYLD_LIBRARY_PATH=.:/Users/foo/Code/lib/boost_1_55/lib
