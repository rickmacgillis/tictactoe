#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __unix__
    #define OS_Windows 0
#elif defined(_WIN32) || defined(WIN32)
    #define OS_Windows 1
#endif

struct GameData {
    short winner;
    short turn;
    int choice;
    bool invalidMove;
    bool gameOver;
    short totalMarked;
    char board[3][3];
};

void printBoard(struct GameData state);
struct GameData enterChoice(int choice, struct GameData state);
bool hasWinner(int choice, struct GameData state);
bool rowsMatch(struct GameData state, int cells[8][3][2]);

int main() {
    struct GameData state;
    state.choice = 0;
    state.winner = 0;
    state.gameOver = false;
    state.turn = 1;
    state.invalidMove = false;
    state.totalMarked = 0;

    state.board[0][0] = '1';
    state.board[0][1] = '2';
    state.board[0][2] = '3';

    state.board[1][0] = '4';
    state.board[1][1] = '5';
    state.board[1][2] = '6';

    state.board[2][0] = '7';
    state.board[2][1] = '8';
    state.board[2][2] = '9';

    while (true) {
        OS_Windows == 1 ? system("cls") : system("clear");
        printBoard(state);
        state.invalidMove = false;

        if (state.gameOver) {
            return 0;
        }

        scanf("%i", &state.choice);
        state = enterChoice(state.choice, state);
    }
}

void printBoard(struct GameData state) {
    printf("      Tic Tac Toe\n\n");
    printf("Player 1 (X) - Player 2 (O)\n\n");

    printf("   |   |   \n");
    printf(" %c | %c | %c \n", state.board[0][0], state.board[0][1], state.board[0][2]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", state.board[1][0], state.board[1][1], state.board[1][2]);
    printf("___|___|___\n");
    printf("   |   |   \n");
    printf(" %c | %c | %c \n", state.board[2][0], state.board[2][1], state.board[2][2]);
    printf("   |   |   \n\n");

    if (state.invalidMove) {
        printf("Invalid move. Try again\n");
    }

    if (state.gameOver && state.winner == 0) {
        printf("Game Over - No Winner.\n");
    } else if (state.winner == 0) {
        printf("Player %i: ", state.turn);
    } else {
        printf("Player %i wins!\n", state.winner);
    }
}

struct GameData enterChoice(int choice, struct GameData state) {
    if (choice < 1 || choice > 9) {
        state.invalidMove = true;
        return state;
    }

    int row = 0;
    int column = choice - 1;
    if (choice >=4 && choice <= 6) {
        row = 1;
        column = choice - 4;
    } else if (choice >=7) {
        row = 2;
        column = choice - 7;
    }

    if (state.board[row][column] == 'X' || state.board[row][column] == 'O') {
        state.invalidMove = true;
        return state;
    }

    char marker = state.turn == 1 ? 'X' : 'O';
    state.board[row][column] = marker;
    state.totalMarked++;
    state.gameOver = state.totalMarked == 9;

    if (hasWinner(choice, state)) {
        state.winner = state.turn;
    } else if (state.gameOver == false) {
        state.turn = state.turn == 1 ? 2 : 1;
    }

    return state;
}

bool hasWinner(int choice, struct GameData state) {
    int cells[8][3][2] = {
        {{ 0, 0 }, { 0, 1 }, { 0, 2 }},
        {{ 1, 0 }, { 1, 1 }, { 1, 2 }},
        {{ 2, 0 }, { 2, 1 }, { 2, 2 }},
        {{ 0, 0 }, { 1, 0 }, { 2, 0 }},
        {{ 0, 1 }, { 1, 1 }, { 2, 1 }},
        {{ 0, 2 }, { 1, 2 }, { 2, 2 }},
        {{ 0, 0 }, { 1, 1 }, { 2, 2 }},
        {{ 0, 2 }, { 1, 1 }, { 2, 0 }},
    };

    return rowsMatch(state, cells);
}

bool rowsMatch(struct GameData state, int cells[8][3][2]) {
    for (int i = 0; i < 8; i++) {
        if (state.board[cells[i][0][0]][cells[i][0][1]] == state.board[cells[i][1][0]][cells[i][1][1]] &&
            state.board[cells[i][0][0]][cells[i][0][1]] == state.board[cells[i][2][0]][cells[i][2][1]]) {
            return true;
        }
    }

    return false;
}
