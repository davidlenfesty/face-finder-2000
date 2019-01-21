# File for which opencv libraries should be linked against
# Needs to have OPENCV_INSTALL_DIR defined previously
list(APPEND OPENCV_LIBS
    "${OPENCV_INSTALL_DIR}/lib/libopencv_core.so"
    "${OPENCV_INSTALL_DIR}/lib/libopencv_highgui.so"
    "${OPENCV_INSTALL_DIR}/lib/libopencv_imgcodecs.so"
    "${OPENCV_INSTALL_DIR}/lib/libopencv_flann.so"
    "${OPENCV_INSTALL_DIR}/lib/libopencv_features2d.so"
    "${OPENCV_INSTALL_DIR}/lib/libopencv_xfeatures2d.so"
)
