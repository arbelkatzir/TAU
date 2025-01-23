#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

// dynamically allocate buffer of buf_size
int allocate_buffer(void **buf, unsigned int buf_size);

// write buf to file and free buf
int write_data_to_file(const char *output_file_path, const unsigned char *buf,
                       unsigned int buf_size);
// read file into newly allocated buf
int load_data_from_file(const char *input_file_path, unsigned char **buf,
                        unsigned int *buf_size);

// load array of words from a file
int load_array_of_words(const char *input_file_path, char ***array,
                        unsigned int *p_cnt);
#endif //__FILE_UTILS_H__
