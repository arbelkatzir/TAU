#include "algs.h"
#include "error_types.h"
#include <string.h>

// TODO: Add the function implementations in here.

// None:
int none_encryption(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;  // Return error if pointers are NULL
    }
    if (size_in > size_out) {
        return ERR_MEMORY; //return ERR_INVALID_SIZE;
    }

    //  copy the input buffer to the output buffer
    memcpy(data_out, data_in, size_in);

    return OK;  // Return OK if successful
}
// Flip Even:
int flip_even(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in > size_out) {
        return ERR_MEMORY; //return ERR_INVALID_SIZE;
    }

    for (unsigned int i = 0; i < size_in; i++) {
        unsigned char byte = data_in[i];
        // Flip even bits: mask the even bits and toggle them
        byte ^= 0x55; // 0x55 is 01010101 in binary (the pattern for even bit positions)
        data_out[i] = byte;
    }

    return OK;
}

// Swap 3:
int swap_3(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in > size_out) {
        return ERR_MEMORY; //return ERR_INVALID_SIZE;
    }

    // Copy input data to output initially
    memcpy(data_out, data_in, size_in);

    // Swap 3 LSB of b1 with 3 MSB of b2 for each pair of bytes
    for (unsigned int i = 0; i < size_in - 1; i += 2) {
        unsigned char b1 = data_in[i];
        unsigned char b2 = data_in[i + 1];

        // Swap 3 LSB of b1 with 3 MSB of b2
        unsigned char swapped_b1 = (b1 & 0xF8) | (b2 >> 5);
        unsigned char swapped_b2 = (b2 & 0x1F) << 5 | (b1 & 0x07);

        // Store the swapped values
        data_out[i] = swapped_b1;
        data_out[i + 1] = swapped_b2;
    }

    return OK;
}

// Rot and Center 5:

int rot_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in > size_out) {
        return ERR_MEMORY; //return ERR_INVALID_SIZE;
    }

    for (unsigned int i = 0; i < size_in; i++) {
        unsigned char byte = data_in[i];

        // Rotate the byte left by 5 bits
        unsigned char rotated = (byte << 5) | (byte >> 3);

        // Split the rotated byte into two bytes and center the result
        unsigned char upper = rotated >> 3;  // Upper 5 bits
        unsigned char lower = rotated & 0x1F; // Lower 5 bits

        // Place the two new bytes into the output buffer
        data_out[2 * i] = upper;
        data_out[2 * i + 1] = lower;
    }

    return OK;
}
//get_size_out
int get_size_out(encrypt_t enc_type, unsigned int size_in) {
    switch (enc_type) {
    case ENC_TYPE_NONE:
        return size_in;
    case ENC_TYPE_FLIP_EVEN:
        return size_in;  // Output size is the same as input
    case ENC_TYPE_SWAP_3:
        return size_in;  // Output size is the same as input
    case ENC_TYPE_ROT_AND_CENTER_5:
        return 2 * size_in;  // Output size is twice the input size (because of split bytes)
    default:
        return ERR_BAD_ENC_TYPE;
    }
}


// TODO : check all decrypt logics
// None (Decryption is identical to encryption for ENC_TYPE_NONE)
int none_decryption(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in > size_out) {
        return ERR_MEMORY; // Return ERR_INVALID_SIZE
    }

    // Simply copy the input buffer to the output buffer
    memcpy(data_out, data_in, size_in);

    return OK;
}

// Flip Even (Decryption is identical to encryption for ENC_TYPE_FLIP_EVEN)
int flip_even_decryption(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in > size_out) {
        return ERR_MEMORY; // Return ERR_INVALID_SIZE
    }

    // XOR with 0x55 again to reverse the flipping of even bits
    for (unsigned int i = 0; i < size_in; i++) {
        unsigned char byte = data_in[i];
        byte ^= 0x55; // XOR with 0b01010101
        data_out[i] = byte;
    }

    return OK;
}

// Swap 3 (Decryption reverses the 3 LSB and 3 MSB swap)
int swap_3_decryption(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in > size_out) {
        return ERR_MEMORY; // Return ERR_INVALID_SIZE
    }

    // Copy input data to output initially
    memcpy(data_out, data_in, size_in);

    // Reverse the 3 LSB of b1 with 3 MSB of b2 swap for each pair of bytes
    for (unsigned int i = 0; i < size_in - 1; i += 2) {
        unsigned char b1 = data_in[i];
        unsigned char b2 = data_in[i + 1];

        // Reverse the 3 LSB and 3 MSB swap
        unsigned char original_b1 = (b1 & 0xF8) | (b2 >> 5);
        unsigned char original_b2 = (b2 & 0x1F) << 5 | (b1 & 0x07);

        // Store the original values
        data_out[i] = original_b1;
        data_out[i + 1] = original_b2;
    }

    return OK;
}

// Rot and Center 5 (Decryption reverses the rotation and centering)
int rot_and_center_5_decryption(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out) {
    if (data_in == NULL || data_out == NULL) {
        return ERR_NULL_PTR;
    }
    if (size_in / 2 > size_out) { // Ensure input size is twice the output size
        return ERR_MEMORY; // Return ERR_INVALID_SIZE
    }

    for (unsigned int i = 0; i < size_out; i++) {
        // Read two input bytes and reassemble the original byte
        unsigned char upper = data_in[2 * i];
        unsigned char lower = data_in[2 * i + 1];

        unsigned char rotated = ((upper & 0x1F) << 3) | ((lower & 0xE0) >> 5);

        // Reverse the rotation
        data_out[i] = (rotated >> 5) | (rotated << 3);
    }

    return OK;
}