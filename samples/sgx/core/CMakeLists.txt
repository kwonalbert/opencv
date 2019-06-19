cmake_minimum_required (VERSION 3.13)
project (opencv_sgx_core_example)

set (opencv_sgx_core_example_VERSION_MAJOR 0)
set (opencv_sgx_core_example_VERSION_MINOR 1)

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

link_directories (${PYTHON_LIBRARY_DIR})

add_untrusted_executable (core_sgx
  SHARED
  SRCS ${src_app}
  EDL ${edl_enclave}
  EDL_SEARCH_PATHS ${edl_paths}
  )

add_dependencies (core_sgx
  enclave
  enclave-sign
  )
