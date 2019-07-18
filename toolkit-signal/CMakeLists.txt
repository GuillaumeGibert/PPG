cmake_minimum_required(VERSION 3.0)

project(toolkit-signal)

set(LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE})

include_directories(./include)

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
	toolkit-signal
	STATIC
	${source_files} 
)