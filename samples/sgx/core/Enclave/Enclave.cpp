#include "Enclave_t.h"

#include "opencv2/core.hpp"

sgx_status_t test_matrix(uint32_t rows, uint32_t cols) {
    cv::Mat A = cv::Mat::eye(rows, cols, CV_32F)*0.1;
    return SGX_SUCCESS;
}
