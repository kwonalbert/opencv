cmake_minimum_required (VERSION 3.13)
project (opencv_sgx_imgproc_example)

set (opencv_sgx_imgproc_example_VERSION_MAJOR 0)
set (opencv_sgx_imgproc_example_VERSION_MINOR 1)

list(APPEND CMAKE_MODULE_PATH $ENV{BADGE_PRODUCT})
find_package(BADGE REQUIRED)

add_subdirectory(Enclave EXCLUDE_FROM_ALL)

set (src_app
  app.cpp
  )

set (edl_enclave
  Enclave/Enclave.edl
  )

set (edl_paths
  Enclave
  )

add_untrusted_executable (imgproc_sgx
  SHARED
  SRCS ${src_app}
  LIBS opencv_core opencv_imgproc opencv_imgcodecs opencv_highgui
  EDL ${edl_enclave}
  EDL_SEARCH_PATHS ${edl_paths}
  )

target_include_directories (imgproc_sgx
  PRIVATE /usr/include/opencv4
  )

target_link_directories (imgproc_sgx
  PRIVATE /usr/lib
  )

add_dependencies (imgproc_sgx
  enclave
  enclave-sign
  )
