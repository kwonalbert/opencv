cmake_minimum_required (VERSION 3.13)
project (opencv_sgx_imgproc_enclave)

set (opencv_sgx_imgproc_enclave_VERSION_MAJOR 0)
set (opencv_sgx_imgproc_enclave_VERSION_MINOR 1)

list(APPEND CMAKE_MODULE_PATH $ENV{BADGE_PRODUCT})
find_package(BADGE REQUIRED)

set (src_enclave
  Enclave.cpp
  )

set (edl_enclave
  Enclave.edl
  )

set (edl_paths
  .
  )

set (badge_libs
  opencv_core
  opencv_imgproc
  )

# badge enclave
add_enclave_library (enclave
  SRCS ${src_enclave}
  DIR Enclave
  BADGE_LIBS ${badge_libs}
  EDL ${edl_enclave}
  EDL_SEARCH_PATHS ${edl_paths}
  )

add_definitions (-DOPENCV_SGX -DNO_GETENV)

target_include_directories (enclave
  PRIVATE /home/me/badge/opencv/build
  PRIVATE /home/me/badge/opencv/include
  PRIVATE /home/me/badge/opencv/modules/core/include
  PRIVATE /home/me/badge/opencv/modules/imgproc/include
  )

target_compile_options (enclave
  PRIVATE "-I/usr/lib/gcc/x86_64-pc-linux-gnu/9.1.0/include"
  )

target_link_directories (enclave
  PRIVATE /home/me/badge/opencv/build/lib
  )

enclave_sign (enclave
  KEY Enclave_private.pem
  CONFIG Enclave.config.xml
  )

if (UNIX)
  set (signed_lib enclave.signed.so)
elseif (WIN32)
  set (signed_lib enclave.signed.lib)
endif ()
