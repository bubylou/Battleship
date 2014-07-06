#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char two_board[8][8], one_board[8][8], one_display[8][8], two_display[8][8];

void draw(char a[8][8], char b[8][8])
{
    int i, j;

    printf("       You                 Computer\n");
    printf("  0 1 2 3 4 5 6 7       0 1 2 3 4 5 6 7\n");

    for (i = 0; i < 8; i++) {
        printf("%d ", i);
        for (j = 0; j < 8; j++) {
            printf("%c ", a[i][j]);
        }

        printf("%d   %d ", i, i);
        for (j = 0; j < 8; j++) {
            printf("%c ", b[i][j]);
        }

        printf("%d\n", i);
    }

    printf("  0 1 2 3 4 5 6 7       0 1 2 3 4 5 6 7\n");
}

void place(int players, int player, char board[8][8])
{
    int i, row, col;

    if (players == 1 && player == 2) {
        for (i = 0; i < 8; i++) {
            row = rand() % 8;
            col = rand() % 8;
            while (board[row][col] != '%') {
                row = rand() % 8;
                col = rand() % 8;
            }

            board[row][col] = '@';
        }
    } else {
        for (i = 0; i < 8; i++) {
            if (player == 1) {
                draw(one_board, two_display);
            } else if (player == 2) {
                draw(one_display, two_board);
            }

            printf("Player %d, Place your ship.\n", player);
            scanf("%d %d", &row, &col);

            while (board[row][col] != '%') {
                printf("Try again.\n");
                scanf("%d %d", &row, &col);
            }

            board[row][col] = '@';
        }
    }
}

void fire(int players, int player)
{
    int row, col;

    if (players == 1 && player == 2) {
        row = rand() % 8;
        col = rand() % 8;

        while (two_board[row][col] == 'X' || two_board[row][col] == 'O') {
            row = rand() % 8;
            col = rand() % 8;
        }

        if (two_board[row][col] == '@') {
            two_board[row][col] = 'O';
            two_display[row][col] = 'O';
        } else if (two_board[row][col] == '%') {
            two_board[row][col] = 'X';
            two_display[row][col] = 'X';
        }
    } else {
        draw(one_display, two_display);

        printf("Player %d, Fire when ready.\n", player);
        scanf("%d %d", &row, &col);

        while (one_board[row][col] == 'X' || one_board[row][col] == 'O') {
            printf("Try again.\n");
            scanf("%d %d", &row, &col);
        }

        if (one_board[row][col] == '@') {
            one_board[row][col] = 'O';
            one_display[row][col] = 'O';
        } else if (one_board[row][col] == '%') {
            one_board[row][col] = 'X';
            one_display[row][col] = 'X';
        }
    }
}

int winner(char board[8][8])
{
    int i, j;
    int hits = 0;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] == '@') {
                return 0;
                if (board[i][j] == 'O') {
                    hits++;
                    if (hits == 8) {
                        return 1;
                    }
                }
            }
        }
    }
}

int main(int argc, char const* argv[])
{
    int i, row, col, players, player;
    char temp_board[8][8] = {'%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%',
                             '%', '%', '%', '%', '%', '%', '%', '%'};

    memcpy(one_board, temp_board, sizeof(temp_board));
    memcpy(two_board, temp_board, sizeof(temp_board));
    memcpy(one_display, temp_board, sizeof(temp_board));
    memcpy(two_display, temp_board, sizeof(temp_board));

    srand(time(NULL));

    printf("Welcome to Battleship.\n");
    printf("% = Water  @ = Ship  X = Miss  O = Hit\n");

    while (players != 1 && players != 2) {
        printf("How many players are there? (1 or 2)\n");
        scanf("%d", &players);
    }

    for (i = 0; i < 8; i++) {
        place(players, 1, one_board);
        place(players, 2, two_board);
    }

    while (winner(one_board) == 0 && winner(two_board) == 0) {
        fire(players, 1);
        fire(players, 2);
    }

    if (winner(two_board) == 1) {
        printf("You Win.\n");
    } else if (winner(one_board) == 2) {
        printf("You Lose.\n");
    }

    return 0;
}
