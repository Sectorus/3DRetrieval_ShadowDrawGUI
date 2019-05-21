# Find includes in corresponding build directories
cmake_minimum_required(VERSION 3.7)
project(ShadowDrawGUI)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


# Instruct CMake to run moc automatically when needed
set (CMAKE_PREFIX_PATH "C:\\QT\\5.12.1\\mingw73_64")
SET("OpenCV_DIR" "C:\\opencv2\\opencv-3.4.5\\mingw-bin\\install")
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
# Find the QtWidgets library
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(img)
file(COPY img DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
file(COPY sketch_ref DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

add_executable(ShadowDrawGUI main.cpp ScribbleArea.cpp ScribbleArea.h MainWindow.cpp MainWindow.h Blending.cpp Blending.h EdgeDetector.cpp EdgeDetector.h ResourceManager.cpp ResourceManager.h Similarity.cpp Similarity.h)
target_link_libraries( ShadowDrawGUI ${OpenCV_LIBS} )
target_link_libraries( ShadowDrawGUI Qt5::Widgets )
# Use the Widgets module from Qt 5



target_link_libraries(ShadowDrawGUI ${OpenCV_LIBS} )
target_link_libraries(ShadowDrawGUI Qt5::Widgets Qt5::Core  )