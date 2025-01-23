#include "file_utils.h"
#include "error_types.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_WORD_SIZE 256

int allocate_buffer(void **buf, unsigned int buf_size) {
    // Allocate memory for the buffer dynamically
    *buf = malloc(buf_size);
    if (*buf == NULL) {
        return ERR_MEMORY; // Return error code for memory allocation failure
    }
    return OK;
}

int write_data_to_file(const char *output_file_path, const unsigned char *buf,
                       unsigned int buf_size) {
    // Open the file for writing in binary mode
    FILE* file = fopen(output_file_path, "wb");
    if (file == NULL) {
        return ERR_FILE; // Return error code if file cannot be opened
    }

    // Write the buffer to the file
    size_t written = fwrite(buf, 1, buf_size, file);
    fclose(file);

    if (written != buf_size) {
        return ERR_FILE; // Return error code if the write operation fails
    }
    return OK;
}

int load_data_from_file(const char *input_file_path, unsigned char **buf,
                        unsigned int *buf_size) {
    // Open the file for reading in binary mode
    FILE* file = fopen(input_file_path, "rb");
    if (file == NULL) {
        return ERR_FILE; // Return error code if file cannot be opened
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    *buf_size = ftell(file);
    rewind(file);

    // Allocate memory for the buffer
    *buf = malloc(*buf_size);
    if (*buf == NULL) {
        fclose(file);
        return ERR_MEMORY; // Return error code for memory allocation failure
    }

    // Read the file into the buffer
    size_t read = fread(*buf, 1, *buf_size, file);
    fclose(file);

    if (read != *buf_size) {
        free(*buf);
        return ERR_FILE; // Return error code if the read operation fails
    }
    return OK;
}

// Function to load blacklisted words from a file
int load_array_of_words(const char *input_file_path, char ***array,
                        unsigned int *p_cnt) {
    // Open the file for reading in text mode
    FILE* file = fopen(input_file_path, "r");
    if (file == NULL) {
        return ERR_FILE; // Return error code if file cannot be opened
    }

    // Count the number of lines in the file
    unsigned int count = 0;
    char word[MAX_WORD_SIZE];
    while (fgets(word, MAX_WORD_SIZE, file) != NULL) {
        count++;
    }
    rewind(file);

    // Allocate memory for the array of strings
    *array = malloc(count * sizeof(char*));
    if (*array == NULL) {
        fclose(file);
        return ERR_MEMORY; // Return error code for memory allocation failure
    }

    // Read each word into the array
    unsigned int index = 0;
    while (fgets(word, MAX_WORD_SIZE, file) != NULL) {
        size_t len = strcspn(word, "\n"); // Remove newline character
        word[len] = '\0';
        (*array)[index] = malloc(len + 1);
        if ((*array)[index] == NULL) {
            // Free previously allocated memory on failure
            for (unsigned int i = 0; i < index; i++) {
                free((*array)[i]);
            }
            free(*array);
            fclose(file);
            return ERR_MEMORY;
        }
        strcpy((*array)[index], word);
        index++;
    }
    fclose(file);

    *p_cnt = count;
    return OK;
}
