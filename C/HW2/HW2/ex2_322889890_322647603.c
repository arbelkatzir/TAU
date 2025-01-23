#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_SUBSEQUENCES 1000

// Global array to store subsequences,helps avoiding duplicates.
char subsequences[MAX_SUBSEQUENCES][100];
int subseq_count = 0; // keeps array length

// Function to check if a subsequence already exists in the array
int contains(char* current) {
    for (int i = 0; i < subseq_count; i++) {
        if (strcmp(subsequences[i], current) == 0) //strcmp = Lexicographic comparison of strings, – Returns 0 if strings are equal
        {
            return 1;  // If the subsequence already exists
        }
    }
    return 0;  // If the subsequence doesn't exist
}

// Recursive function to generate subsequences
void generate_subsequences(char* str, char* current, int index) {
    if (str[index] == '\0') {
        // If the subsequence is not already in the array, add it
        if (!contains(current)) {
            strcpy(subsequences[subseq_count], current);  // Save to the array
            printf("%s\n", current);
            subseq_count++;  // Increment the count of subsequences array length
        }
        return;
    }

    // Include the current character
    current[strlen(current)] = str[index];
    current[strlen(current) + 1] = '\0';  // Null-terminate the string
    generate_subsequences(str, current, index + 1);

    // Exclude the current character
    current[strlen(current) - 1] = '\0';  // Remove the current character
    generate_subsequences(str, current, index + 1);
}



int main() {
    char str[100];
    char current[100] = "";

    // Input from the user
    printf("Enter a string: ");
    scanf("%s", str);

    // Print the subsequences
    printf("Subsequences:\n");
    generate_subsequences(str, current, 0);
    return 0;
}


