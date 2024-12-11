#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define board_size 10
void print_board(char board[board_size][board_size], int board_real_size);

int main()
{
    int board_real_size; // Variable to store the board size
    char board[board_size][board_size]; // Static 10x10 array

    // Welcome message and prompt for board size
    printf("Please enter the board size N [1-10]:\n");
    scanf("%d", &board_real_size);

    // Initialize the board with the '-' character
    for (int i = 0; i < board_real_size; i++) {
        for (int j = 0; j < board_real_size; j++) {
            board[i][j] = '-'; // Set each cell to '-'
        }
    }

    // Print the welcome message for the Tic-Tac-Toe game
    printf("Welcome to %dx%d Tic-Tac-Toe:\n", board_real_size, board_real_size);
    print_board(board, board_real_size);

    
	return 0;
}

void print_board(char board[board_size][board_size], int board_real_size) {
    for (int i = 0; i < board_real_size; i++) {
        for (int j = 0; j < board_real_size; j++) {
            printf("%c ", board[i][j]); // Print each cell with a space
        }
        printf("\n"); // Move to the next row after printing a row
    }
}
