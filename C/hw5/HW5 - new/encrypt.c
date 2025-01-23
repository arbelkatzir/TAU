#include "encrypt.h"
#include "error_types.h"
#include "file_utils.h"

#include <stdio.h>

int encrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type) {
    unsigned char* input_buf = NULL;  // Input buffer to hold file data
    unsigned char* output_buf = NULL; // Output buffer for encrypted data
    unsigned int buf_size = 0;        // Size of the input file in bytes
    int result;

    // Step 1: Load input file into a dynamically allocated buffer
    result = load_data_from_file(input_file_path, &input_buf, &buf_size);
    if (result != OK) {
        return result; // Return error if loading fails
    }

    // Step 2: Allocate memory for the output buffer
    result = allocate_buffer(&output_buf, buf_size);
    if (result != OK) {
        free(input_buf);
        return result; // Return error if loading fails
    }

    // Step 3: Validate the encryption type
    if (enc_type < ENC_TYPE_NONE || enc_type >= ENC_TYPE_LAST) {
        free(input_buf);
        return ERR_BAD_ENC_TYPE;
    }

    // Step 4: Perform encryption based on the specified encryption type
    switch (enc_type) {
        case ENC_TYPE_NONE: {
            result = none_encryption(input_buf, buf_size, output_buf, buf_size);
            break;
        }
        case ENC_TYPE_FLIP_EVEN: {
            result = flip_even(input_buf, buf_size, output_buf, buf_size);
            break;
        }

        case ENC_TYPE_SWAP_3: {
            result = swap_3(input_buf, buf_size, output_buf, buf_size);
            break;
        }

        case ENC_TYPE_ROT_AND_CENTER_5: {
            // Free the existing output buffer and allocate a new one with twice the size
            free(output_buf);
            result = allocate_buffer(&output_buf, 2 * buf_size); // Output buffer is twice the input size
            if (result != OK) {
                free(input_buf);
                return result;
            }

            result = flip_even(input_buf, buf_size, output_buf, 2* buf_size);
            break;
        }


        default: {
            // Handle unsupported encryption types
            free(input_buf);
            free(output_buf);
            return ERR_BAD_ENC_TYPE; // Unsupported encryption type
        }
    }

    // Step 5: Write the encrypted data to the output file
    result = write_data_to_file(output_file_path, output_buf, buf_size);

    // Step 6: Clean up dynamically allocated memory
    free(input_buf);
    free(output_buf);

    return result; // Return the result of the file write operation
}


// TODO check this!!!!!!!
int decrypt_file(const char *input_file_path, const char *output_file_path, encrypt_t enc_type) {
    unsigned char* input_buf = NULL;  // Input buffer to hold encrypted data
    unsigned char* output_buf = NULL; // Output buffer for decrypted data
    unsigned int buf_size = 0;        // Size of the input file in bytes
    int result;

    // Step 1: Load input file into a dynamically allocated buffer
    result = load_data_from_file(input_file_path, &input_buf, &buf_size);
    if (result != OK) {
        return result; // Return error if loading fails
    }

    // Step 2: Validate the encryption type
    if (enc_type < ENC_TYPE_NONE || enc_type >= ENC_TYPE_LAST) {
        free(input_buf);
        return ERR_BAD_ENC_TYPE;
    }

    // Step 3: Allocate memory for the output buffer
    unsigned int output_buf_size = buf_size; // Default size matches input size
    if (enc_type == ENC_TYPE_ROT_AND_CENTER_5) {
        output_buf_size = buf_size / 2; // For ROT_AND_CENTER_5, output size is half of input size
    }

    result = allocate_buffer(&output_buf, output_buf_size);
    if (result != OK) {
        free(input_buf);
        return result; // Return error if allocation fails
    }

    // Step 4: Perform decryption based on the specified encryption type
    switch (enc_type) {
        case ENC_TYPE_NONE: {
            result = none_decryption(input_buf, buf_size, output_buf, output_buf_size);
            break;
        }
        case ENC_TYPE_FLIP_EVEN: {
            result = flip_even_decryption(input_buf, buf_size, output_buf, output_buf_size);
            break;
        }

        case ENC_TYPE_SWAP_3: {
            result = swap_3_decryption(input_buf, buf_size, output_buf, output_buf_size);
            break;
        }

        case ENC_TYPE_ROT_AND_CENTER_5: {
            result = rot_and_center_5_decryption(input_buf, buf_size, output_buf, output_buf_size);
            break;
        }

        default: {
            // Handle unsupported encryption types
            free(input_buf);
            free(output_buf);
            return ERR_BAD_ENC_TYPE;
        }
    }

    // Step 5: Write the decrypted data to the output file
    if (result == OK) {
        result = write_data_to_file(output_file_path, output_buf, output_buf_size);
    }

    // Step 6: Clean up dynamically allocated memory
    free(input_buf);
    free(output_buf);

    return result; // Return the result of the file write operation or decryption
}
