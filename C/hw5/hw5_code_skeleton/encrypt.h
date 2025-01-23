#ifndef __ENCRYPT_H__
#define __ENCRYPT_H__

#include "algs.h" // for encrypt_t

// Encrypt input file and dump the result to output file, according to the given
// encryption type
int encrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type);

// Decryption function (reverse of encryption)
int decrypt_file(const char *input_file_path, const char *output_file_path,
                 encrypt_t enc_type);

#endif //__ENCRYPT_H__
