cmake_minimum_required(VERSION 3.13)
project(ShadowDrawGUI)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(img)
file(COPY img DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(ShadowDrawGUI main.cpp)
target_link_libraries( ShadowDrawGUI ${OpenCV_LIBS} )
target_link_libraries( ShadowDrawGUI Qt5::Widgets )