



include_directories(${SOURCE_DIR})
include_directories(${INCLUDE_OUTPUT_PATH})
include_directories(${PROJECT_SOURCE_DIR} )


link_directories(${LIBRARY_OUTPUT_PATH})


# Collect sources into the variable MATH_SOURCES with
# having to explicitly list each header and source file
file (GLOB GAME_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}  *.h *.hpp *.txt)

# Collect sources into the variable DreamCoreLib_Src
file (GLOB Game_Src *.txt *.h *.cpp)


add_executable (${ProjectName} ${Game_Src} )


target_link_libraries (${ProjectName} NetLib)

set_property(TARGET ${ProjectName} PROPERTY FOLDER "Executables")


