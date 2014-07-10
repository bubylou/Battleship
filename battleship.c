#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct data {
    int boats;
    char board[8][8];
    char display[8][8];
} playerone, playertwo;

void draw(char a[8][8], char b[8][8])
{
    int i, j;

    printf("     Player #1             Player #2\n");
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
    printf("      Boats: %d             Boats: %d\n",
            playerone.boats, playertwo.boats);
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
            playertwo.boats++;
        }
    } else {
        for (i = 0; i < 8; i++) {
            if (player == 1) {
                draw(playerone.board, playertwo.display);
            } else if (player == 2) {
                draw(playerone.display, playertwo.board);
            }

            printf("Player %d, Place your ship.\n", player);
            scanf("%d %d", &row, &col);

            while (board[row][col] != '%') {
                printf("Try again.\n");
                scanf("%d %d", &row, &col);
            }

            board[row][col] = '@';

            if (player == 1) playerone.boats++;
            if (player == 2) playertwo.boats++;
        }
    }
}

void fire(int players, int player, char board[8][8], char display[8][8])
{
    int row, col;

    if (players == 1 && player == 2) {
        row = rand() % 8;
        col = rand() % 8;

        while (board[row][col] == 'X' || board[row][col] == 'O') {
            row = rand() % 8;
            col = rand() % 8;
        }

        if (board[row][col] == '@') {
            board[row][col] = display[row][col] = 'O';
            playerone.boats--;
        } else if (board[row][col] == '%') {
            board[row][col] = display[row][col] = 'X';
        }
    } else {
        draw(playerone.display, playertwo.display);

        printf("Player %d, Fire when ready.\n", player);
        scanf("%d %d", &row, &col);

        while (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Try again.\n");
            scanf("%d %d", &row, &col);
        }

        if (board[row][col] == '@') {
            board[row][col] = display[row][col] = 'O';
            if (player == 1) playertwo.boats--;
            if (player == 2) playerone.boats--;
        } else if (board[row][col] == '%') {
            board[row][col] = display[row][col] = 'X';
        }
    }
}

int main(int argc, char const* argv[])
{
    int i, row, col, players, player;
    char board[8][8] = {'%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%',
                        '%', '%', '%', '%', '%', '%', '%', '%'};

    memcpy(playerone.board, board, sizeof(board));
    memcpy(playertwo.board, board, sizeof(board));
    memcpy(playerone.display, board, sizeof(board));
    memcpy(playertwo.display, board, sizeof(board));

    srand(time(NULL));

    printf("Welcome to Battleship.\n");
    printf("% = Water  @ = Ship  X = Miss  O = Hit\n");

    while (players != 1 && players != 2) {
        printf("How many players are there? (1 or 2)\n");
        scanf("%d", &players);
    }

    place(players, 1, playerone.board);
    place(players, 2, playertwo.board);

    while (playerone.boats != 0 && playertwo.boats != 0) {
        fire(players, 1, playertwo.board, playertwo.display);
        fire(players, 2, playerone.board, playerone.display);
    }

    if (playerone.boats == 0 && playertwo.boats == 0) {
        printf("Tie.\n");
    } else {
        if (playertwo.boats == 0) printf("Player 1 Wins.\n");
        if (playerone.boats == 0) printf("Player 2 Wins.\n");
    }

    return 0;
}
