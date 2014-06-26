#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void draw(char board[8][8])
{
    int i, j;

    printf("  0 1 2 3 4 5 6 7\n");

    for (i = 0; i <= 7; i++) {
        printf("%d ", i);
        for (j = 0; j <= 7; j++) {
            printf("%c ", board[i][j]);
        }

        printf("%d\n", i);
    }

    printf("  0 1 2 3 4 5 6 7\n");
}

void place(char comp_board[8][8], char user_board[8][8])
{
    int i, row, column;

    for (i = 0; i <= 7; i++) {
        row = rand() % 8;
        column = rand() % 8;
        if (comp_board[row][column] != '%') {
            row = rand() % 8;
            column = rand() % 8;
        }

        comp_board[row][column] = '@';
    }

    for (i = 0; i <= 7; i++) {
        draw(user_board);
        printf("Place your ship.\n");
        scanf("%d %d", &row, &column);
        if (user_board[row][column] != '%') {
            printf("Try again.\n");
            scanf("%d %d", &row, &column);
        }

        user_board[row][column] = '@';
    }
}

void fire(char comp_board[8][8], char user_board[8][8])
{
    int row, column;

    row = rand() % 8;
    column = rand() % 8;

    if (user_board[row][column] == 'X' || user_board[row][column] == 'O') {
        row = rand() % 8;
        column = rand() % 8;
    } else if (user_board[row][column] == '@') {
        user_board[row][column] = 'O';
    } else if (user_board[row][column] == '%') {
        user_board[row][column] = 'X';
    }

    printf("Fire when ready.\n");
    scanf("%d %d", &row, &column);

    if (comp_board[row][column] == 'X' || comp_board[row][column] == 'O') {
        printf("Try again.\n");
        scanf("%d %d", &row, &column);
    } else if (comp_board[row][column] == '@') {
        comp_board[row][column] = 'O';
    } else if (comp_board[row][column] == '%') {
        comp_board[row][column] = 'X';
    }
}

int winner(char board[8][8])
{
    int i, j;

    for (i = 0; i <= 7; i++) {
        for (j = 0; j <= 7; j++) {
            if (board[i][j] == '@') {
                return 0;
            }
        }
    }

    return 1;
}

int main(void)
{
    int i, row, column;
    char comp_board[8][8], user_board[8][8];
    char base_board[8][8] = {'%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%'};

    srand(time(NULL));
    memcpy(comp_board, base_board, sizeof(base_board));
    memcpy(user_board, base_board, sizeof(base_board));

    printf("Welcome to Battleship.\n");
    printf("% = Water  @ = Ship  X = Miss  O = Hit\n");

    place(comp_board, user_board);

    while (winner(user_board) == 0 && winner(comp_board) == 0) {
        printf("\nComputer\n");
        draw(comp_board);
        printf("--------------------");
        printf("\nYou\n");
        draw(user_board);
        fire(comp_board, user_board);
    }

    if (winner(comp_board) == 1) {
        printf("You Win.\n");
    } else if (winner(user_board) == 1) {
        printf("You Lose.\n");
    }

    return 0;
}
