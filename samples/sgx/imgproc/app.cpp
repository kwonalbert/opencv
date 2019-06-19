#include "Enclave_u.h"

#include "opencv2/opencv.hpp"

#include "sgx_urts.h"

#include <stdio.h>

int main() {
    sgx_enclave_id_t eid = 0;

    sgx_launch_token_t token = {0};
    sgx_status_t ret_status, sgx_status;
    int updated = 0;

    sgx_status = sgx_create_enclave("Enclave/enclave.signed.so", 1,
    				    &token, &updated, &eid, NULL);
    if (sgx_status != SGX_SUCCESS) {
	printf("creating enclave failed: %d\n", sgx_status);
        return 1;
    }

    cv::Mat img = cv::imread("test.tif");
    cv::Size img_size = img.size();
    size_t size = img.total() * img.elemSize();

    uint8_t *bytes = new uint8_t[size];
    std::memcpy(bytes, img.data, size);


    uint8_t *res = new uint8_t[size];
    sgx_status = test_imgproc(eid, &ret_status,
			      (uint32_t) img_size.height,
			      (uint32_t) img_size.width,
			      bytes, size, res, size);
    if (sgx_status != SGX_SUCCESS) {
	delete[] bytes;
	delete[] res;
	printf("imgproc test failed.");
        return 1;
    } else if (ret_status != SGX_SUCCESS) {
	delete[] bytes;
	delete[] res;
	printf("imgproc test failed internally.");
        return 1;
    }

    cv::Mat blurred = cv::Mat(img_size.height, img_size.width,
			      CV_8UC3, res);

    cv::imshow("Original", img);
    cv::imshow("Blurred", blurred);

    cv::waitKey(0);

    delete[] bytes;
    delete[] res;
    return 0;
}
