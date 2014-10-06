cmake_minimum_required(VERSION 2.8)


set(LibName "NetLib")


include_directories(${INCLUDE_OUTPUT_PATH})
include_directories(.)



link_directories("${LIBRARY_OUTPUT_PATH}")


# Collect sources into the variable MATH_SOURCES with
# having to explicitly list each header and source file
file (GLOB DREAM_SOURCES *.h *.hpp *.txt)


# Collect sources into the variable DreamCoreLib_Src
file (GLOB DreamCore_Core_Src
"*.txt"
"*.h"
"*.cpp")




# Create named folders for the sources within the .vcproj
# Empty name lists them directly under the .vcproj
source_group("" FILES ${DreamCore_SOURCES})
source_group("Core" FILES ${DreamCore_Core_Src})


# Set Properties->General->Configuration Type to Dynamic Library(.dll)
# Creates DreamCoreLib.dll with the listed sources collected in the variables
# Also adds sources to the Solution Explorer
add_library( ${LibName} 
	${DreamCore_SOURCES} 
	${DreamCore_Core_Src}
	)

	
set_property(TARGET ${LibName} PROPERTY FOLDER "Library")
set_property(TARGET ${LibName} PROPERTY LINKER_LANGUAGE CXX) 



