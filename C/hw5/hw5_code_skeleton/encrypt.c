#include "encrypt.h"
#include "error_types.h"
#include "file_utils.h"
#include <stdlib.h>
#include <string.h>

int encrypt_file(const char *input_file_path, const char *output_file_path, encrypt_t enc_type) {
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
            // No encryption, just copy input to output
            memcpy(output_buf, input_buf, buf_size);
            break;
        }
        case ENC_TYPE_FLIP_EVEN: {
            for (unsigned int i = 0; i < buf_size; i++) {
                output_buf[i] = input_buf[i] ^ 0xAA; // XOR with 0b10101010
            }
            break;
        }

        case ENC_TYPE_SWAP_3: {
            for (unsigned int i = 0; i + 1 < buf_size; i += 2) {
                unsigned char b1 = input_buf[i];       // First byte in the pair
                unsigned char b2 = input_buf[i + 1];   // Second byte in the pair

                // Extract and swap the 3 LSB of b1 with the 3 MSB of b2
                unsigned char b1_lsb = b1 & 0x07;       // 3 LSB of b1
                unsigned char b2_msb = b2 & 0xE0;       // 3 MSB of b2

                // Perform the swap
                b1 = (b1 & 0xF8) | (b2_msb >> 5);      // Replace 3 LSB of b1 with 3 MSB of b2
                b2 = (b2 & 0x1F) | (b1_lsb << 5);      // Replace 3 MSB of b2 with 3 LSB of b1

                // Store the results
                output_buf[i] = b1;
                output_buf[i + 1] = b2;
            }

            // If there’s an odd byte left at the end, copy it unchanged
            if (buf_size % 2 != 0) {
                output_buf[buf_size - 1] = input_buf[buf_size - 1];
            }
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

            for (unsigned int i = 0; i < buf_size; i++) {
                // Rotate the input byte left by 5 bits
                unsigned char rotated = (input_buf[i] << 5) | (input_buf[i] >> 3);

                // Split the rotated value into two bytes
                output_buf[2 * i] = (rotated & 0xF8) >> 3; // First byte: 5 MSBs of the rotated value
                output_buf[2 * i + 1] = (rotated & 0x07) << 5; // Second byte: 3 LSBs of the rotated value, shifted to MSBs
            }

            buf_size *= 2; // Update buffer size since the output is twice the input
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

int decrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type) {
    unsigned char* input_buf = NULL;  // Input buffer
    unsigned char* output_buf = NULL; // Output buffer
    unsigned int buf_size = 0;        // Size of the input file
    int result;

    // Step 1: Load the input file into a buffer
    result = load_data_from_file(input_file_path, &input_buf, &buf_size);
    if (result != OK) {
        return result; // Return error if loading fails
    }

    // Step 2: Allocate buffer for the output
    // Handle specific case for ENC_TYPE_ROT_AND_CENTER_5 since it has a larger buffer size in encryption
    if (enc_type == ENC_TYPE_ROT_AND_CENTER_5) {
        result = allocate_buffer((void**)&output_buf, buf_size / 2);
    }
    else {
        result = allocate_buffer((void**)&output_buf, buf_size);
    }

    if (result != OK) {
        free(input_buf);
        return result; // Return error if allocation fails
    }

    // Step 3: Validate encryption type
    if (enc_type < ENC_TYPE_NONE || enc_type >= ENC_TYPE_LAST) {
        free(input_buf);
        free(output_buf);
        return ERR_BAD_ENC_TYPE;
    }

    // Step 4: Decrypt based on the encryption type
    switch (enc_type) {
    case ENC_TYPE_NONE: {
        // No decryption needed, just copy input to output
        memcpy(output_buf, input_buf, buf_size);
        break;
    }

    case ENC_TYPE_FLIP_EVEN: {
        // XOR with 0xAA to undo flipping even bits
        for (unsigned int i = 0; i < buf_size; i++) {
            output_buf[i] = input_buf[i] ^ 0xAA; // XOR with 0b10101010
        }
        break;
    }

    case ENC_TYPE_SWAP_3: {
        for (unsigned int i = 0; i + 1 < buf_size; i += 2) {
            unsigned char b1 = input_buf[i];
            unsigned char b2 = input_buf[i + 1];

            // Extract the swapped bits and reverse them
            unsigned char b1_lsb = b1 & 0x07;       // 3 LSB of b1
            unsigned char b2_msb = b2 & 0xE0;       // 3 MSB of b2

            // Reassemble the original bytes
            b1 = (b1 & 0xF8) | (b2_msb >> 5);      // Restore 3 LSB of b1
            b2 = (b2 & 0x1F) | (b1_lsb << 5);      // Restore 3 MSB of b2

            // Store the results
            output_buf[i] = b1;
            output_buf[i + 1] = b2;
        }

        // If there’s an odd byte left at the end, copy it unchanged
        if (buf_size % 2 != 0) {
            output_buf[buf_size - 1] = input_buf[buf_size - 1];
        }
        break;
    }

    case ENC_TYPE_ROT_AND_CENTER_5: {
        for (unsigned int i = 0; i < buf_size / 2; i++) {
            unsigned char b1 = input_buf[2 * i];       // First byte of split
            unsigned char b2 = input_buf[2 * i + 1];   // Second byte of split

            // Recombine the original rotated byte
            unsigned char combined = ((b1 << 3) & 0xF8) | ((b2 >> 5) & 0x07);

            // Reverse the left rotation by 5
            output_buf[i] = (combined >> 5) | (combined << 3);
        }
        break;
    }

    default: {
        free(input_buf);
        free(output_buf);
        return ERR_BAD_ENC_TYPE; // Unsupported encryption type
    }
    }

    // Step 5: Write the decrypted data to the output file
    result = write_data_to_file(output_file_path, output_buf, buf_size / (enc_type == ENC_TYPE_ROT_AND_CENTER_5 ? 2 : 1));

    // Step 6: Clean up and return
    free(input_buf);
    free(output_buf);
    return result;
}
