#define _CRT_NONSTDC_NO_DEPRECATE // For strdup

#include "file_utils.h"
#include "error_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_SIZE 256

int allocate_buffer(void **buf, unsigned int buf_size) {
  // TODO 
    *buf = malloc(buf_size);
    if (*buf == NULL) {
        return ERR_MEMORY;// Return error if memory allocation fails

    }

  return OK;
}

int write_data_to_file(const char *output_file_path, const unsigned char *buf,
                       unsigned int buf_size) {
  // TODO
    FILE* file = fopen(output_file_path, "wb");
    if (file == NULL) {
        return ERR_FILE; // Return error if file cannot be opened
    }
    // Write the buffer data to the file
    size_t written = fwrite(buf, 1, buf_size, file); 
    if (written != buf_size) {
        fclose(file);
        return ERR_FILE;
    }
    fclose(file);
    free((void*)buf);
  return OK;
}

int load_data_from_file(const char *input_file_path, unsigned char **buf,
                        unsigned int *buf_size) {
  // TODO
    FILE* file = fopen(input_file_path, "rb");
    if (file == NULL) {
        return ERR_FILE;// Return error if file cannot be opened
    }
    //find size of file
    fseek(file, 0, SEEK_END);
    *buf_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    //allocate memory for the buffer
    int result = allocate_buffer((void**)buf, *buf_size);
    if (result != OK) {
        fclose(file);
        return result;
    }
    // Read the file contents into the buffer
    size_t read_size = fread(*buf, 1, *buf_size, file);
    if (read_size != *buf_size) {
        fclose(file);
        free(*buf);  // Free the allocated memory in case of error
        return ERR_FILE;  // Return error if the reading process fails
    }
    fclose(file);
  return OK;
}

// Function to load blacklisted words from a file
int load_array_of_words(const char *input_file_path, char ***array,
                        unsigned int *p_cnt) {
  // TODO
    FILE* file = fopen(input_file_path, "r");
    if (file == NULL) {
        return ERR_FILE;  // Return error if file cannot be opened
    }

    // Initialize the counter for the number of words
    *p_cnt = 0;

    // Allocate memory for the array of words (10 words initially)
    char** temp_array = malloc(sizeof(char*) * 10);
    if (temp_array == NULL) {
        fclose(file);
        return ERR_MEMORY;  // Return error if memory allocation fails
    }

    char word[MAX_WORD_SIZE];  // Buffer for each word

    // Read each word from the file
    while (fgets(word, sizeof(word), file) != NULL) {
        word[strcspn(word, "\n")] = 0;  // Remove the newline character

        // Duplicate the word and store it in the array
        temp_array[*p_cnt] = strdup(word);
        if (temp_array[*p_cnt] == NULL) {
            fclose(file);

            // Clean up previously allocated memory before returning
            for (unsigned int i = 0; i < *p_cnt; i++) {
                free(temp_array[i]);
            }
            free(temp_array);
            return ERR_MEMORY;
        }

        (*p_cnt)++;

        // Check if we need to resize the array
        if (*p_cnt % 10 == 0) {
            // Resize the array to hold more words (increase size by 10)
            char** temp = realloc(temp_array, sizeof(char*) * (*p_cnt + 10));
            if (temp == NULL) {
                fclose(file);

                // Clean up previously allocated memory before returning
                for (unsigned int i = 0; i < *p_cnt; i++) {
                    free(temp_array[i]);
                }
                free(temp_array);
                return ERR_MEMORY;
            }
            temp_array = temp;  // Update temp_array with the resized array
        }
    }

    fclose(file);

    // Assign the dynamically allocated array to the output pointer
    *array = temp_array;
  
  return OK;
}
