# I don't know what I'm doing.
# This really isn't the best CMakeLists.txt.
# It kind of assumes that directories are hardcoded.
# It also assumes you have a version of OpenCV installed with SURF.

# TODO: add support for using SIFT instead

cmake_minimum_required(VERSION 3.0)
project(Face-Finder-2000)

# Includes OpenCV libraries and defines OPENCV_LIBS variable
include("${CMAKE_CURRENT_SOURCE_DIR}/opencv_libs.cmake")


add_executable(find_face face_finder.cpp)
target_link_libraries(find_face ${OPENCV_LIBS})
target_compile_options(find_face PUBLIC -Werror)
