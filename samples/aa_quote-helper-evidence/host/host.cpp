// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <openenclave/attestation/sgx/evidence.h>
#include <openenclave/host.h>
#include <stdio.h>
#include <unistd.h>

#include "getting_report_u.h"

// SGX Remote Attestation UUID.
static oe_uuid_t sgx_remote_uuid = {OE_FORMAT_UUID_SGX_ECDSA};

int main(int argc, const char* argv[])
{
    oe_result_t result;
    int ret = 1;
    oe_enclave_t* enclave = NULL;
    oe_uuid_t* format_id = &sgx_remote_uuid;

    uint32_t flags = OE_ENCLAVE_FLAG_DEBUG;

    uint8_t* pem_key = NULL;
    size_t pem_key_size = 0;
    uint8_t* evidence = NULL;
    size_t evidence_size = 0;
    uint8_t* format_settings = NULL;
    size_t format_settings_size = 0;

    char* enclave_name = "Enclave_A";

    if (argc != 2)
    {
        fprintf(
            stderr, "Usage: %s enclave_image_path [ --simulate  ]\n", argv[0]);
        goto exit;
    }

    // Create the enclave
    result = oe_create_getting_report_enclave(
        argv[1], OE_ENCLAVE_TYPE_AUTO, flags, NULL, 0, &enclave);
    if (result != OE_OK)
    {
        fprintf(
            stderr,
            "oe_create_getting_report_enclave(): result=%u (%s)\n",
            result,
            oe_result_str(result));
        goto exit;
    }
    else
    {
        printf("Host: Enclave successfully created.\n");
    }

    printf("Host: Requesting %s format settings\n", enclave_name);
    result = get_enclave_format_settings(
        enclave,
        &ret,
        format_id,
        &format_settings,
        &format_settings_size);
    if ((result != OE_OK) || (ret != 0))
    {
        printf("Host: get_format_settings failed. %s\n", oe_result_str(result));
        if (ret == 0)
            ret = 1;
        goto exit;
    }
    // Call into the enclave
    // result = enclave_getting_report(enclave);
    // if (result != OE_OK)
    // {
    //     fprintf(
    //         stderr,
    //         "calling into enclave_getting_report failed: result=%u (%s)\n",
    //         result,
    //         oe_result_str(result));
    //     goto exit;
    // }








    ret = 0;

exit:
    // Clean up the enclave if we created one
    if (enclave)
        oe_terminate_enclave(enclave);

    return ret;
}
