# Includes files and such that OpenCV requires

set(OPENCV_INSTALL_DIR "/usr" CACHE STRING "Location of OpenCV installation")
set(OPENCV_INC_DIR "include" CACHE STRING "Directory that contains OpenCV includes")
set(OPENCV_LIB_DIR "lib" CACHE STRING "Directory that contains OpenCV libraries")

include_directories("/usr/local/include")

set(OPENCV_LIB_PREFIX ${OPENCV_INSTALL_DIR}/${OPENCV_LIB_DIR})

list(APPEND OPENCV_LIBS
    "${OPENCV_LIB_PREFIX}/libopencv_core.so"
    "${OPENCV_LIB_PREFIX}/libopencv_highgui.so"
    "${OPENCV_LIB_PREFIX}/libopencv_imgcodecs.so"
    "${OPENCV_LIB_PREFIX}/libopencv_flann.so"
    "${OPENCV_LIB_PREFIX}/libopencv_features2d.so"
    "${OPENCV_LIB_PREFIX}/libopencv_xfeatures2d.so"
)
