# Version check
cmake_minimum_required (VERSION 3.17)
cmake_policy(SET CMP0015 NEW)

if(NOT "${CMAKE_CXX_STANDARD}")
	set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
  if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  endif()
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/module)

# Project
project(CppWebExploration)

#include_directories("lib/assimp/include")
#link_directories("lib/assimp/lib-js")
#link_libraries("assimp")

# Add files
file(GLOB sources main.cpp)

# Add Executable
#add_library(${PROJECT_NAME} STATIC ${sources})
add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC "..")

# Compiler Options
set(COMMON_OPTIONS -fexceptions -g -Wall -pedantic-errors -pedantic)
set(DEBUG_OPTIONS ${COMMON_OPTIONS})
set(RELEASE_OPTIONS -O3 ${COMMON_OPTIONS})
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")

set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s DEMANGLE_SUPPORT=1 --no-entry --bind -s NO_EXIT_RUNTIME=1 --pre-js=\"../cmake/emsdk_prejs.js\"")
target_include_directories(${PROJECT_NAME} PUBLIC "D:/msys2/mingw64/include" ".." "../cpp-pre/type_traits")