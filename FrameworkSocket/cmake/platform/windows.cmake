message(STATUS "Setting up Windows enviroment")


# Command to output information to the console
# Useful for displaying errors, warnings, and debugging
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /wd4800 /we4263 /we4264 /wd4334")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_definitions(-D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES)
add_definitions(-D_WIN32_WINNT="0x0501")