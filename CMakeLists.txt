cmake_minimum_required(VERSION 3.13)
project(3D)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(3D main.cpp)
target_link_libraries( 3D ${OpenCV_LIBS} )