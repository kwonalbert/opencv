#include "Enclave_t.h"

#include "opencv2/core.hpp"

double test_matrix(uint32_t rows, uint32_t cols) {
    cv::Mat A = cv::Mat::eye(rows, cols, CV_32F) * 0.1;
    double sum = cv::sum(A)[0];
    return sum;
}
