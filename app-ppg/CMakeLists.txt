cmake_minimum_required(VERSION 3.0)

project(app-ppg)

set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})

include_directories(./include)

include_directories(${TOOLKIT_IMAGE_INCLUDE_DIR})
include_directories(${TOOLKIT_QT_INCLUDE_DIR})
include_directories(${TOOLKIT_SIGNAL_INCLUDE_DIR})
include_directories(${TOOLKIT_TRACKING_INCLUDE_DIR})


include_directories(${OPENCV_INCLUDE_DIR})

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})



link_directories(${OPENCV_LIB_DIR})

link_directories(${QT_LIB_DIR})

file(
	GLOB_RECURSE source_files
	src/*/*.cpp
	include/*/*.h
	ui/*/*.ui
) 
 

group_src("${source_files}")

add_executable(
	app-ppg
	${source_files} 
)

target_link_libraries(

        app-ppg

	
	${TOOLKIT_IMAGE_LIBRARY}
	${TOOLKIT_QT_LIBRARY}
	${TOOLKIT_SIGNAL_LIBRARY}
	${TOOLKIT_TRACKING_LIBRARY}
	
	Qt5::Widgets
	Qt5::Core
	Qt5::Gui
	Qt5::OpenGL
	
	${OPENCV_CORE_LIBRARY}
	${OPENCV_HIGHGUI_LIBRARY}
	${OPENCV_IMPROC_LIBRARY}
	${OPENCV_ML_LIBRARY}
	${OPENCV_VIDEOIO_LIBRARY}
	${OPENCV_DNN_LIBRARY}
       
      	${MISC_OPENGL_LIBRARY}
	${MISC_GLU_LIBRARY}
	${MISC_WS_LIBRARY}
	${MISC_IPHLP_LIBRARY}
	${MISC_SETUP_LIBRARY}
)


