#ifndef __CENSOR_H__
#define __CENSOR_H__

#include "algs.h" // for encrypt_t

// censor and encrypt main function
int censor_and_encrypt(const char *input_path, const char *output_censored_path,
                       encrypt_t enc_type, const char *blacklist_path);

#endif //__CENSOR_H__
