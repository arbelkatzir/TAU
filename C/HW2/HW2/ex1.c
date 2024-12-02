#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// SECTION A: Recursive Palindrome Check
int is_palindrome_recursive(char* str, int start, int end) {
    // TODO: Implement the logic for recursive palindrome check
    int size = strlen(str);
    if (size == 2 && str[start] == str[end]) {
        return 1;
    }
    if (size == 1) {
        return 1;
    }
    if (str[start] != str[end]) {
        return 0;
    }


    str[end] = '\0';
    str++;
    end = strlen(str) - 1;

    int out = is_palindrome_recursive(str, start, end);
    return out; // Placeholder return value
}

// SECTION B: Iterative Palindrome Check
int is_palindrome_iterative(char* str) {
    // TODO: Implement the logic for iterative palindrome check
    for 
    return 0; // Placeholder return value
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
