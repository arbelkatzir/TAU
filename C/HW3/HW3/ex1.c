#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define board_size 10
void print_board(char board[board_size][board_size], int real_board_size);
void play(char board[board_size][board_size], int real_board_size, int curr_player);
int invalid_indices(char board[board_size][board_size], int real_board_size, int row, int col);

int main()
{
    int real_board_size; // Variable to store the board size
    char board[board_size][board_size]; // Static 10x10 array
    int curr_player = 1;

    // Welcome message and prompt for board size
    printf("Please enter the board size N [1-10]:\n");
    scanf("%d", &real_board_size);

    // Initialize the board with the '-' character
    for (int i = 0; i < real_board_size; i++) {
        for (int j = 0; j < real_board_size; j++) {
            board[i][j] = '-'; // Set each cell to '-'
        }
    }

    // Print the welcome message for the Tic-Tac-Toe game
    printf("Welcome to %dx%d Tic-Tac-Toe:\n", real_board_size, real_board_size);
    print_board(board, real_board_size);

    play(board, real_board_size, 1);
    
	return 0;
}

void print_board(char board[board_size][board_size], int real_board_size) {
    for (int i = 0; i < real_board_size; i++) {
        for (int j = 0; j < real_board_size; j++) {
            printf("%c ", board[i][j]); // Print each cell with a space
        }
        printf("\n"); // Move to the next row after printing a row
    }
}

void play(char board[board_size][board_size], int real_board_size, int curr_player) {
    int row, col;
    printf("Player %d, please insert your move:\n", curr_player);
    scanf("%d , %d", &row, &col);

    // check if the cell is empty 
    while (invalid_indices(board, real_board_size, row, col)) {
        printf("Invalid indices, please choose your move again:\n");
        scanf("%d , %d", &row, &col);
    }

    board[row - 1][col - 1] = (curr_player == 1) ? 'X' : 'O';
    print_board(board, real_board_size);
}

int invalid_indices(char board[board_size][board_size], int real_board_size, int row, int col) {
    if (board[row - 1 ][col - 1] != '-') {
        return 1;
    }
    if (row < 1 || row > board_size) {
        return 1;
    }
    if (col < 1 || col > board_size) {
        return 1;
    }
    return 0;
}