cmake_minimum_required(VERSION 3.0)

project(toolkit-image)

set(LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE})

include_directories(./include)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})

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