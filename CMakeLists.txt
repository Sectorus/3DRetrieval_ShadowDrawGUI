cmake_minimum_required(VERSION 3.13)
project(ShadowDrawGUI)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(ShadowDrawGUI main.cpp)
target_link_libraries( ShadowDrawGUI ${OpenCV_LIBS} )