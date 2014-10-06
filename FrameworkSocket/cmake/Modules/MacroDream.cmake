



macro(opt OPTION HELP VALUE)
	option(ENABLE_${OPTION} ${HELP} ${VALUE})
	set(OPT_TEXI "${OPT_TEXI}\n@item ENABLE_${OPTION}\n${HELP} (default: ${VALUE})")
endmacro(opt)

macro(set_proj_Folder PROJECT_TARGET_NAME FOLDER_NAME)
	set_property(TARGET ${PROJECT_TARGET_NAME} PROPERTY FOLDER ${FOLDER_NAME})
endmacro(set_proj_Folder)



macro(find_all_libraries VARNAME LISTNAME PATH SUFFIX)
	set(${VARNAME})
	list(LENGTH ${LISTNAME} NUM_LIST)
	foreach(LIB ${${LISTNAME}})
		find_library(FOUND_LIB ${LIB} PATHS ${PATH} PATH_SUFFIXES ${SUFFIX})
		if(FOUND_LIB)
			list(APPEND ${VARNAME} ${FOUND_LIB})
		endif(FOUND_LIB)
		unset(FOUND_LIB CACHE)
	endforeach(LIB)

	list(LENGTH ${VARNAME} NUM_FOUND_LIBRARIES)
	if(NUM_FOUND_LIBRARIES LESS NUM_LIST)
		set(${VARNAME})
	endif(NUM_FOUND_LIBRARIES LESS NUM_LIST)
endmacro(find_all_libraries)

macro(set_config_option VARNAME STRING)
	set(${VARNAME} TRUE)
	list(APPEND CONFIG_OPTIONS ${STRING})
	message(STATUS "Found " ${STRING})
endmacro(set_config_option)

if(APPLE)
##https://gist.github.com/sixman9/740257
#It might be possible to use the ${NAME} variable value (i.e. substituted for the 'MyApp' name)
#ADD_FRAMEWORK(AudioToolbox MyApp)
#ADD_FRAMEWORK(CoreGraphics MyApp)
#ADD_FRAMEWORK(QuartzCore MyApp)
#ADD_FRAMEWORK(UIKit MyApp)

	# Set xcode project property
	# ref : https://code.google.com/p/ios-cmake/source/browse/toolchain/iOS.cmake
	macro (set_xcode_property TARGET XCODE_PROPERTY XCODE_VALUE)
		set_property (TARGET ${TARGET} PROPERTY XCODE_ATTRIBUTE_${XCODE_PROPERTY} ${XCODE_VALUE})
	endmacro (set_xcode_property)

	macro(ADD_FRAMEWORK fwname appname)
		find_library(FRAMEWORK_${fwname}
        NAMES ${fwname}
        PATHS ${CMAKE_OSX_SYSROOT}/System/Library
        PATH_SUFFIXES Frameworks
        NO_DEFAULT_PATH)
		if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
			MESSAGE(ERROR ": Framework ${fwname} not found")
		else()
			TARGET_LINK_LIBRARIES(${appname} ${FRAMEWORK_${fwname}})
			MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
		endif()
	endmacro(ADD_FRAMEWORK)
endif(APPLE)
