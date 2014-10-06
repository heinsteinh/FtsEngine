#https://github.com/gcsmith/gchip/tree/95005c6d5ce2489854d0ae56d41e6ffeec31055d/cmake/Modules

cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

set(ProjectName "NetWorkProgramming")
project(${ProjectName} CXX C)




if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type: None Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif(NOT CMAKE_BUILD_TYPE)


# Allow cmake to create folder 
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MAKEDREAM_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${MAKEDREAM_MODULE_PATH} ${MAKEDREAM_MODULE_PATH})



# -- config output directories
set(EXECUTABLE_OUTPUT_PATH 		${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH 		${PROJECT_SOURCE_DIR}/lib)
set(INCLUDE_OUTPUT_PATH 		${PROJECT_SOURCE_DIR}/include)



# -- config source directories
set(SOURCE_DIR 			${PROJECT_SOURCE_DIR}/FrameworkCommon)



include(${MAKEDREAM_MODULE_PATH}/MacroDream.cmake)
include(${MAKEDREAM_MODULE_PATH}/DetectPlatform.cmake)



opt(BUILD_LIB "Enable 'lib' target for building static DreamCode library" OFF)
opt(BUILD_SHARED "Enable 'shared' target for building shared DreamCode library" OFF)
opt(BUILD_DYNAMIC "Enable dynamic DreamCode executable (linked with shared lib)" OFF)




include(CheckTypeSize)
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckCXXCompilerFlag)


include(${MAKEDREAM_MODULE_PATH}/BuildingPlatform.cmake)



#set output directory
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib" )


add_subdirectory(${SOURCE_DIR})
add_subdirectory(SocketServer)



message(STATUS "--------------------------------------------------------------")
message(STATUS "")
message(STATUS "DREAMCODE ${DREAMCODE_VERSION} has been configured for ${DREAMCODE_OS}")
message(STATUS "")
message(STATUS " * Build options:" ${DREAMCODE_CONFIG_OPTIONS})
message(STATUS " * Build type: " ${CMAKE_BUILD_TYPE})
message(STATUS " * C compiler: " ${CMAKE_C_COMPILER})
message(STATUS " * C++ compiler: " ${CMAKE_CXX_COMPILER})
message(STATUS " * Install prefix: " ${CMAKE_INSTALL_PREFIX})
message(STATUS "")
