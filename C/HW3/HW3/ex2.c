#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 10  // Maximum length of the search string
#define MAX_POOL 20    // Maximum number of strings in the pool

// Function prototypes
void count_chars(const char* str, int count[256]);
int are_counts_equal(const int count1[256], const int count2[256]);

int main() {
    char search[MAX_LENGTH + 1];              // Array to store the search string
    char pool[MAX_POOL][MAX_POOL + 1];        // Array to store the strings pool
    int num_strings = 0, num_permutations = 0; // Counters for strings and permutations
    int search_count[256], current_count[256]; // Arrays to store character counts

    // Prompt the user to enter the search string
    printf("Enter the search string:\n");
    scanf("%s", search);

    // Count the characters in the search string
    count_chars(search, search_count);

    printf("Enter the strings pool:\n");
    while (num_strings < MAX_POOL && scanf("%s", pool[num_strings]) != EOF) {
        num_strings++; // Count the number of strings read
    }


    // Iterate through each string in the pool
    for (int i = 0; i < num_strings; i++) {
        // Check if the current string has the same length as the search string
        if (strlen(pool[i]) == strlen(search)) {
            // Count the characters in the current string
            count_chars(pool[i], current_count);
            // Compare the character counts to determine if it's a permutation
            if (are_counts_equal(search_count, current_count)) {
                num_permutations++; // Increment the permutation count
            }
        }
    }

    // Print the result
    printf("Number of permutations of \"%s\" in the strings pool is: %d\n", search, num_permutations);
    return 0;
}

// Function to count the frequency of each character in a string
void count_chars(const char* str, int count[256]) {
    memset(count, 0, sizeof(int) * 256); // Initialize the count array to 0
    while (*str) {
        count[tolower(*str)]++; // Increment the count for the lowercase character
        str++;
    }
}

// Function to compare two character count arrays
int are_counts_equal(const int count1[256], const int count2[256]) {
    for (int i = 0; i < 256; i++) {
        if (count1[i] != count2[i]) {
            return 0; // Arrays are not equal
        }
    }
    return 1; // Arrays are equal
}
