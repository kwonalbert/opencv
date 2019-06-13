#include "Enclave_u.h"

#include "sgx_urts.h"

#include <stdio.h>

int main() {
    sgx_enclave_id_t eid = 0;

    sgx_launch_token_t token = {0};
    sgx_status_t ret_status, sgx_status;
    int updated = 0;
    // TODO: second parameter is the debug parameter.
    // need to change 1 to 0 for release..
    sgx_status = sgx_create_enclave("enclave.signed.so", 1,
    				    &token, &updated, &eid, NULL);
    if (sgx_status != SGX_SUCCESS) {
	printf("creating enclave failed: %d\n", sgx_status);
        return 1;
    }

    sgx_status = test_matrix(eid, &ret_status, 300, 300);
    if (sgx_status != SGX_SUCCESS) {
	printf("creating matrix failed");
        return 1;
    }

    return 0;
}
