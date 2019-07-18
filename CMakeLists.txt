cmake_minimum_required(VERSION 3.0)

#####CMAKE#####
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../dist" CACHE FILEPATH "path to dist directory")

####################
# MACRO
####################

MACRO(GROUP_SRC SRCS) 
  foreach(FILE ${SRCS})  
    #convert source file to absolute
    get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
    # Get the directory of the absolute source file
    get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
    # Remove common directory prefix to make the group
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}") 
    # Make sure we are using windows slashes
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    # Group into "Source Files" and "Header Files" and "Ui Files"
    if ("${FILE}" MATCHES ".*\\.cpp")
	  string(REPLACE "\\src" "" GROUP "${GROUP}")
      set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
	  string(REPLACE "\\include" "" GROUP "${GROUP}")
      set(GROUP "Header Files${GROUP}")
	elseif("${FILE}" MATCHES ".*\\.ui")
	  string(REPLACE "\\ui" "" GROUP "${GROUP}")
	  set(GROUP "Ui Files${GROUP}")
	  set(UI_PATH "${UI_PATH};${PARENT_DIR}")
	elseif("${FILE}" MATCHES ".*\\.qrc")
	  string(REPLACE "\\ui" "" GROUP "${GROUP}")
	  set(GROUP "Ui Files${GROUP}")
    endif() 
    source_group("${GROUP}"  FILES "${FILE}")
  endforeach()  
  set(CMAKE_AUTOUIC_SEARCH_PATHS "${UI_PATH}")
ENDMACRO(GROUP_SRC)


project(ppg) 

####################
# 3rd parties libraries
####################

#####AUTO######

#QT
set(CMAKE_PREFIX_PATH "C:/Qt/5.11.1/msvc2015_64"  CACHE FILEPATH "path to qt5 vs2015 directory")
find_package(Qt5Widgets)
find_package(Qt5Gui)
find_package(Qt5Core)
find_package(Qt5OpenGL)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ./ui)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

#####MANUAL######

#OPENCV
set(OPENCV_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../3rdparty/opencv/opencv-4.0/include" CACHE FILEPATH "path to opencv include directory")
set(OPENCV_LIB_DIR "${CMAKE_SOURCE_DIR}/../3rdparty/opencv/opencv-4.0/lib" CACHE FILEPATH "path to opencv lib directory")
set(OPENCV_CORE_LIBRARY optimized opencv_core400 debug opencv_core400d)
set(OPENCV_HIGHGUI_LIBRARY optimized opencv_highgui400 debug  opencv_highgui400d)
set(OPENCV_IMPROC_LIBRARY optimized opencv_imgproc400 debug opencv_imgproc400d)
set(OPENCV_ML_LIBRARY optimized opencv_ml400 debug opencv_ml400d)
set(OPENCV_VIDEOIO_LIBRARY optimized opencv_videoio400 debug opencv_videoio400d)
set(OPENCV_DNN_LIBRARY optimized opencv_dnn400 debug opencv_dnn400d)

# MISC
set(MISC_OPENGL_LIBRARY optimized opengl32 debug opengl32)
set(MISC_GLU_LIBRARY optimized glu32 debug glu32)
set(MISC_WS_LIBRARY optimized ws2_32 debug ws2_32)
set(MISC_IPHLP_LIBRARY optimized iphlpapi debug iphlpapi)
set(MISC_SETUP_LIBRARY optimized setupapi debug setupapi)

####################
# project libraries
####################

# toolkit

set(TOOLKIT_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/toolkit-image/include" CACHE FILEPATH "path to toolkit-image include directory")
set(TOOLKIT_QT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/toolkit-qt/include" CACHE FILEPATH "path to toolkit-qt include directory")
set(TOOLKIT_SIGNAL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/toolkit-signal/include" CACHE FILEPATH "path to toolkit-signal include directory")
set(TOOLKIT_TRACKING_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/toolkit-tracking/include" CACHE FILEPATH "path to toolkit-tracking include directory")

set(TOOLKIT_IMAGE_LIBRARY optimized toolkit-image debug toolkit-image)
set(TOOLKIT_QT_LIBRARY optimized toolkit-qt debug toolkit-qt)
set(TOOLKIT_SIGNAL_LIBRARY optimized toolkit-signal debug toolkit-signal)
set(TOOLKIT_TRACKING_LIBRARY optimized toolkit-tracking debug toolkit-tracking)

####################
# add project subdirectories
####################

# toolkit
add_subdirectory(toolkit-image)
add_subdirectory(toolkit-qt)
add_subdirectory(toolkit-signal)
add_subdirectory(toolkit-tracking)

# app
add_subdirectory(app-ppg)

####################
# INSTALL
####################

# bin, lib
install(DIRECTORY ${CMAKE_BINARY_DIR}/bin DESTINATION .)
install(DIRECTORY ${CMAKE_BINARY_DIR}/lib DESTINATION .)

# include
install(DIRECTORY ${TOOLKIT_IMAGE_INCLUDE_DIR} DESTINATION .)
install(DIRECTORY ${TOOLKIT_QT_INCLUDE_DIR} DESTINATION .)
install(DIRECTORY ${TOOLKIT_SIGNAL_INCLUDE_DIR} DESTINATION .)
install(DIRECTORY ${TOOLKIT_TRACKING_INCLUDE_DIR} DESTINATION .)


####################
# set startup project
####################
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app-ppg)
set_target_properties(app-ppg PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/../dist/bin/$(Configuration)")
