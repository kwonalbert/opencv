#include "Enclave_t.h"

#include "opencv2/imgproc.hpp"

sgx_status_t test_imgproc(uint32_t height,
			  uint32_t width,
			  uint8_t *matrix,
			  uint32_t matrix_size,
			  uint8_t *out,
			  uint32_t out_size) {
    cv::Mat img = cv::Mat(height, width, CV_8UC3, matrix);
    blur(img, img, cv::Size(17,17));

    std::memcpy(out, img.data, out_size);
    return SGX_SUCCESS;
}
