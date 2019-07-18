cmake_minimum_required(VERSION 3.0)

project(toolkit-image)

set(LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE})

include_directories(./include)

include_directories(${OPENCV_INCLUDE_DIR})

file(
	GLOB_RECURSE
	source_files
	src/*.cpp
	include/*.h
)
    
add_library(
	toolkit-image
	STATIC
	${source_files} 
)