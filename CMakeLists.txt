cmake_minimum_required (VERSION 2.6)

project (dwMalloc)

ADD_DEFINITIONS("-std=c++0x -stdlib=libc++ -Os") 

# The version number
set (dwMalloc_VERSION_MAJOR 0)
set (dwMalloc_VERSION_MINOR 1)

SET(BASEPATH "${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES("${BASEPATH}")


SET( CMAKE_LINKER_FLAGS
    "-stdlib=libc++" CACHE STRING
    "Use recent c++ standard library."
    FORCE )
    
    
add_library (dwMalloc  malloc.cpp dwMalloc.cpp)

add_executable (test2 test1/test2.cpp)
target_link_libraries (test2 dwMalloc -stdlib=libc++ -Os)

add_test (Test2Runs test2 1 1 1 1)
add_test (Test2Runs2 test2 1 1 1 1)