
if(WIN32)

	set(PLATFORM_WINDOWS 1)
	set(DREAMCODE_OS " ${CMAKE_SYSTEM_NAME}")

	message(STATUS " ")
	message(STATUS "##################################################")
	message(STATUS "Building for platform: Windows                    ")
	message(STATUS "Building for platform name: ${DREAMCODE_OS}       ")
	message(STATUS "##################################################")
	message(STATUS " ")

	opt(BUILD_WINDOWS "Enable Windows library target " ON)
	opt(BUILD_MAC "Enable Mac OS X library target " OFF)
	opt(BUILD_UNIX "Enable Unix library target " OFF)


	set(MKPROP WIN32)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /TP -W2")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /TP -W2")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
	
	set(PLATFORM_UNIX 1)


	set(BUILD_BACKEND_IOS OFF)
	set(BUILD_BACKEND_ANDROID ON)

	set(PLATFORM_BACKEND_MAC OFF)
	set(PLATFORM_BACKEND_UNIX OFF)
	set(PLATFORM_BACKEND_WINDOWS ON)

	set(HAVE_OPENGLES OFF)
	set(HAVE_OPENGL OFF)
	set(HAVE_GLES ON)
	set(HAVE_EGL ON)


elseif(APPLE)

	set(PLATFORM_APPLE 1)
	set(DREAMCODE_OS " ${CMAKE_SYSTEM_NAME}")
	message(STATUS "")
	message(STATUS "##################################################")
	message(STATUS "Building for platform: APPLE                      ")
	message(STATUS "Building for platform name: ${DREAMCODE_OS}       ")
	message(STATUS "##################################################")
	message(STATUS "")
	

	opt(BUILD_WINDOWS "Enable Windows library target " OFF)
	opt(BUILD_MAC "Enable Mac OS X library target " ON)
	opt(BUILD_UNIX "Enable Unix library target " OFF)
	opt(BUILD_IOS "Enable Unix library target " OFF)
	
	
	set(MKPROP MACOSX_BUNDLE)	
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -std=c99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
	set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} rt m)
	
	
	set(BUILD_BACKEND_IOS OFF)
	set(BUILD_BACKEND_ANDROID OFF)

	set(PLATFORM_BACKEND_MAC ON)
	set(PLATFORM_BACKEND_UNIX OFF)
	set(PLATFORM_BACKEND_WINDOWS OFF)

	set(HAVE_OPENGLES ON)
	set(HAVE_OPENGL OFF)
	set(HAVE_GLES OFF)
	set(HAVE_EGL OFF)


elseif(UNIX)

	set(PLATFORM_UNIX 1)
	set(DREAMCODE_OS " ${CMAKE_SYSTEM_NAME}")
	message(STATUS "")
	message(STATUS "##################################################")
	message(STATUS "Building for platform: UNIX                       ")
	message(STATUS "Building for platform name: ${DREAMCODE_OS}       ")
	message(STATUS "##################################################")
	message(STATUS "")

	opt(BUILD_WINDOWS "Enable Windows library target " OFF)
	opt(BUILD_MAC "Enable Mac OS X library target " OFF)
	opt(BUILD_UNIX "Enable Unix library target " ON)


	set(MKPROP "")	
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -std=c99")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")
	set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} rt m)
	add_definitions(-D_GNU_SOURCE)
	

	set(HAVE_OPENGLES OFF)
	set(HAVE_GLES OFF)

else()

	message(FATAL_ERROR "Unsupported platform detected")
endif()
