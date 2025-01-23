#include <stdio.h>

char* strrchr(char s[], char c) {
    if (!s) { // Check for NULL input
        return NULL;
    }

    char* last_occur = NULL;

    // Traverse the string
    while (*s) {
        if (*s == c) {        // Update last occurrence if the character matches
            last_occur = s;
        }
        s++;
    }

    return last_occur; // Return last occurrence or NULL if not found
}

int main() {
    char str[] = "abcb"; // Define the string
    char c = 'b';        // Character to search

    // Call strrchr and store the result
    char* result = strrchr(str, c);

    if (result) {
        printf("Last occurrence of '%c': %s\n", c, result); // Print the result
    }
    else {
        printf("Character '%c' not found in the string.\n", c);
    }

    return 0;
}
