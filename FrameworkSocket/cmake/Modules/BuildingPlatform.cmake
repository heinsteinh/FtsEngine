

#useful to set warning as error when compiling
#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#    set(warnings "-Wall -Wextra -Werror")
#elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
#    set(warnings "/W4 /WX /EHsc")
#endif()

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()



if(ENABLE_BUILD_WINDOWS)


	message("Compiler: MSVC, version: " ${MSVC_VERSION})
		
	# Disable display of the copyright banner
	# Set common win32 defines
	# Disable Warning 4127
	# Enable exception handling
	# Float Modell: precise
	# Embedding type whcar_t
	# Enable RTTI
	set(CMAKE_C_FLAGS "/nologo /W4 /DWIN32 /D_WINDOWS /wd4127 /EHsc /fp:precise /Zc:wchar_t /Zc:forScope /GR")
	set(CMAKE_CXX_FLAGS "/nologo /W4 /DWIN32 /D_WINDOWS /wd4127 /EHsc /fp:precise /Zc:wchar_t /Zc:forScope /GR")
	set(PREPROCESSOR_DEFINITIONS "${PREPROCESSOR_DEFINITIONS} -DUNICODE -D_UNICODE")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D _CRT_SECURE_NO_WARNINGS")
	
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
	# Enable intrinsics on MSVC in debug mode
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Oi")

	# unicode support
    add_definitions( -DUNICODE -D_UNICODE )
    
    #misc define
    add_definitions( -D_CRT_SECURE_NO_WARNINGS )
    add_definitions( -D_CRT_SECURE_NO_DEPRECATE )
    add_definitions( -D_CRT_NONSTDC_NO_DEPRECATE )

	
    if((MSVC_VERSION EQUAL 1800) OR (MSVC_VERSION EQUAL 1700))
	# MSVC 2012 / 2013
	message(STATUS "MSVC_VERSION: ${MSVC_VERSION}")
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /sdl /Ob0 /GF- /GS")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /sdl /GS")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /Gm- /fp:except-")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /sdl /Ob0 /GF- /GS")
	set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /sdl /GS")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Gm- /fp:except-")
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /SAFESEH:NO")
	set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} /SAFESEH:NO")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /SAFESEH:NO")

	SET(CMAKE_CXX_FLAGS "/EHsc") 	
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/windows" )
	
     endif()
	
elseif(ENABLE_BUILD_MAC)
	
		
        set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
	
	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -g -Wall")
	
	set(XCODE_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer")

	file (GLOB _XCODE_SDKS "${XCODE_ROOT}/SDKs/*")
	
	if (_XCODE_SDKS)
		list (SORT _XCODE_SDKS)
		list (GET _XCODE_SDKS 0 XCODE_SDK_ROOT)
	else ()
		message (FATAL_ERROR "No Mac SDK's found in default search path ${XCODE_ROOT}.")
	endif ()
	
	message (STATUS "Toolchain using default SDK: ${XCODE_SDK_ROOT}")
	set(CMAKE_OSX_SYSROOT "${XCODE_SDK_ROOT}")

	find_library(FWCORESERVICES CoreServices)
	find_library(FWCOREAUDIO CoreAudio)
	find_library(FWCOREVIDEO CoreVideo)
	find_library(FWQTKIT QTKit)
	find_library(FWOPENGL OpenGL)
	find_library(FWAUDIOTOOLBOX AudioToolbox)
	find_library(FWAPPLICATIONSERVICES ApplicationServices)
	find_library(FWFOUNDATION Foundation)
	find_library(FWAPPKIT AppKit)
	find_library(FWSECURITY Security)
	find_library(FWIOKIT IOKit)
	
	set(all_libs
	${LIBWEBRTC}
	${FWCORESERVICES}
	${FWCOREAUDIO}
	${FWCOREVIDEO}
	${FWQTKIT}
	${FWOPENGL}
	${FWAUDIOTOOLBOX}
	${FWAPPLICATIONSERVICES}
	${FWFOUNDATION}
	${FWAPPKIT}
	${FWSECURITY}
	${FWIOKIT}
	-lcrypto
	-lssl
	)

	#set(XCODE_ATTRIBUTE_SDKROOT ${CMAKE_OSX_SYSROOT})
    
	set( CMAKE_OSX_DEPLOYMENT_TARGET "10.9")
	set( CMAKE_OSX_ARCHITECTURES "x86_64")
	set( CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework OpenGL -framework OpenAL -lz -framework GLUT")
    
	#add_definitions(-Wno-reorder)
	#add_definitions(-msse)


    	#set output directory
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/macos" )
    
	

elseif(ENABLE_BUILD_UNIX)

    #set output directory
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/unix/${CMAKE_BUILD_TYPE}" )
   
#BUILD_PLATFORM_IOS


elseif( ENABLE_BUILD_IOS )


	include(${CMAKE_SOURCE_DIR}/cmake/platform/ios.cmake)
	
	set(ENABLE_BUILD_MAC ON)

	set( CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework CoreGraphics -framework QuartzCore
	 -framework UIKit -framework OpenGLES -framework OpenAL")

	set( MACOSX_BUNDLE_GUI_IDENTIFIER "com.yourcompany.\${PRODUCT_NAME:rfc1034identifier}")
	

	#set output directory
	set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/ios" )


# if (IOS_PLATFORM MATCHES OS)
#	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}/Release-iphoneos)
#	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}/Debug-iphoneos)
#elseif (IOS_PLATFORM MATCHES SIMULATOR)

	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${LIBRARY_OUTPUT_PATH}/Release-iphonesimulator)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${LIBRARY_OUTPUT_PATH}/Debug-iphonesimulator)


	set(CMAKE_CXX_FLAGS "-std=c++0x")
	#set(CMAKE_CXX_FLAGS "-x objective-c++")
	set(CMAKE_EXE_LINKER_FLAGS "-framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit")


	set(CMAKE_OSX_SYSROOT "${CMAKE_IOS_SDK_ROOT}")

	find_library(FWCORESERVICES CoreServices)
	find_library(FWCOREAUDIO CoreAudio)
	find_library(FWCOREVIDEO CoreVideo)
	find_library(FWOPENGLES OpenGLES)

	

else()
	message(FATAL_ERROR "Unsupported platform detected")
endif()
