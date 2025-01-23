#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// SECTION A: Recursive Palindrome Check
int is_palindrome_recursive(char* str, int start, int end) {
    // Base case: if we've reached the middle
    if (start >= end) {
        return 1;
    }

    // Check if the characters are the same, ignoring case and non-alphanumeric characters
    if (!isalnum(str[start])) {
        return is_palindrome_recursive(str, start + 1, end);  // Skip non-alphanumeric characters
    }
    if (!isalnum(str[end])) {
        return is_palindrome_recursive(str, start, end - 1);  // Skip non-alphanumeric characters
    }
    if (tolower(str[start]) != tolower(str[end])) {
        return 0;  // If the characters don't match, it's not a palindrome
    }

    // Recurse for the next pair of characters
    return is_palindrome_recursive(str, start + 1, end - 1);
}


// SECTION B: Iterative Palindrome Check
int is_palindrome_iterative(char* str) {
    int start = 0;
    int end = strlen(str) - 1;

    while (start < end) {
        // Skip non-alphanumeric characters
        if (!isalnum(str[start])) {
            start++;
        }
        else if (!isalnum(str[end])) {
            end--;
        }
        else if (tolower(str[start]) != tolower(str[end])) {
            return 0;  // If the characters don't match, it's not a palindrome
        }
        else {
            start++;
            end--;
        }
    }
    return 1;  // If we've compared all the characters successfully
}


// Driver Program
int main() {
    char str[1000];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Remove newline character
    str[strcspn(str, "\n")] = '\0';

    printf("\nResults:\n");
    printf("Recursive Palindrome Check: %s\n", is_palindrome_recursive(str, 0, strlen(str) - 1) ? "Palindrome" : "Not a Palindrome");
    printf("Iterative Palindrome Check: %s\n", is_palindrome_iterative(str) ? "Palindrome" : "Not a Palindrome");
    return 0;
}
