#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define board_size 10
void print_board(char board[board_size][board_size], int real_board_size);
void move(char board[board_size][board_size], int real_board_size, int curr_player);
int invalid_indices(char board[board_size][board_size], int real_board_size, int row, int col);
int check_rows(char board[board_size][board_size], int real_board_size);
int check_columns(char board[board_size][board_size], int real_board_size);
int check_diagonals(char board[board_size][board_size], int real_board_size);
int check_tie(char board[board_size][board_size], int real_board_size);


int main()
{
    int real_board_size; // Variable to store the board size
    char board[board_size][board_size]; // Static 10x10 array
    int curr_player = 1; // Player 1 starts
    int winner = 0; // 0 - ongoing, 1 - player 1 wins, 2 - player 2 wins, 3 - tie
    int game_is_on = 1; // Game loop control

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

    // Main game loop
    while (game_is_on) {
        // Current player makes a move
        move(board, real_board_size, curr_player);

        // Check the game's status
        winner = check_rows(board, real_board_size);
        if (winner == 0) winner = check_columns(board, real_board_size);
        if (winner == 0) winner = check_diagonals(board, real_board_size);
        if (winner == 0) winner = check_tie(board, real_board_size);

        // If a winner or tie is found, end the game
        if (winner != 0) {
            game_is_on = 0;
        }
        else {
            // Switch to the next player
            curr_player = (curr_player == 1) ? 2 : 1;
        }
    }

    // Announce the result
    if (winner == 1) {
        printf("Player 1 is the winner!\n");
    }
    else if (winner == 2) {
        printf("Player 2 is the winner!\n");
    }
    else if (winner == 3) {
        printf("There is a Tie!\n");
    }
    
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

void move(char board[board_size][board_size], int real_board_size, int curr_player) {
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
    if (row < 1 || row > real_board_size || col < 1 || col > real_board_size) {
        return 1; // Out-of-bounds indices
    }
    if (board[row - 1][col - 1] != '-') {
        return 1; // Cell already occupied
    }
    return 0;
}


int check_rows(char board[board_size][board_size], int real_board_size) {
    for (int row = 0; row < real_board_size; row++) {
        char curr_cell = board[row][0];
        if (curr_cell != '-') {
            int row_winner = 1;
            for (int col = 1; col < real_board_size; col++) {
                if (board[row][col] != curr_cell) {
                    row_winner = 0;
                    break;
                }
            }
            if (row_winner) {
                return (curr_cell == 'X') ? 1 : 2;
            }
        }
    }
    return 0; // No winner in rows
}

int check_columns(char board[board_size][board_size], int real_board_size) {
    for (int col = 0; col < real_board_size; col++) {
        char curr_cell = board[0][col];
        if (curr_cell != '-') {
            int col_winner = 1;
            for (int row = 1; row < real_board_size; row++) {
                if (board[row][col] != curr_cell) {
                    col_winner = 0;
                    break;
                }
            }
            if (col_winner) {
                return (curr_cell == 'X') ? 1 : 2;
            }
        }
    }
    return 0; // No winner in columns
}

int check_diagonals(char board[board_size][board_size], int real_board_size) {
    // Check main diagonal
    char curr_cell = board[0][0];
    if (curr_cell != '-') {
        int diag_winner = 1;
        for (int i = 1; i < real_board_size; i++) {
            if (board[i][i] != curr_cell) {
                diag_winner = 0;
                break;
            }
        }
        if (diag_winner) {
            return (curr_cell == 'X') ? 1 : 2;
        }
    }

    // Check secondary diagonal
    curr_cell = board[0][real_board_size - 1];
    if (curr_cell != '-') {
        int diag_winner = 1;
        for (int i = 1; i < real_board_size; i++) {
            if (board[i][real_board_size - 1 - i] != curr_cell) {
                diag_winner = 0;
                break;
            }
        }
        if (diag_winner) {
            return (curr_cell == 'X') ? 1 : 2;
        }
    }

    return 0; // No winner in diagonals
}

int check_tie(char board[board_size][board_size], int real_board_size) {
    for (int row = 0; row < real_board_size; row++) {
        for (int col = 0; col < real_board_size; col++) {
            if (board[row][col] == '-') {
                return 0; // There is still space, not a tie
            }
        }
    }
    return 3; // It's a tie
}