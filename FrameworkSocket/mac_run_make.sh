

# For benefit of log files.
echo pwd = `pwd`
echo $0 $*
# Make sure bash fails completely if any command fails
set -e




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

#make
#xcodebuild -list



xcodebuild  -configuration Debug



cd ../../

cd bin

cd macos

cd Debug


echo 'Executing the Debug'


./ProjectBuilder


#open ProjectBuilder.xcodeproj
