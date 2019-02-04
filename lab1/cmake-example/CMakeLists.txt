cmake_minimum_required (VERSION 3.5)
project (Simple)
set (CMAKE_CXX_STANDARD 11)

# The version number.
set (Simple_VERSION_MAJOR 1)
set (Simple_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/SimpleConfig.h.in"
  "${PROJECT_BINARY_DIR}/SimpleConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find SimpleConfig.h
include_directories("${PROJECT_BINARY_DIR}")

include_directories ("${PROJECT_SOURCE_DIR}/testlib")
add_subdirectory (testlib) 

# add the executable
 add_executable(SimpleMain main.cc)
target_link_libraries (SimpleMain TestLib)
