#ifndef __algs_H__
#define __algs_H__

typedef enum {
  ENC_TYPE_NONE = 0,

  ENC_TYPE_FLIP_EVEN,
  ENC_TYPE_SWAP_3,
  ENC_TYPE_ROT_AND_CENTER_5,

  ENC_TYPE_LAST
} encrypt_t;

// the different encryption functions

/* TODO: add your decleration here.
 * The signature should look like:
 *
 * int func_name(const unsigned char *data_in, unsigned int size_in, unsigned
 * char *data_out, unsigned int size_out);
 */
int none_encryption(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);
int flip_even(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);
int swap_3(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);
int rot_and_center_5(const unsigned char* data_in, unsigned int size_in, unsigned char* data_out, unsigned int size_out);
int get_size_out(encrypt_t enc_type, unsigned int size_in);


#endif //__algs_H__
