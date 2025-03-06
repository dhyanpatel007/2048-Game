#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility.h"



#define SIZE 4



int gameover(int gameboard[SIZE][SIZE]);

void printboard(int gameboard[SIZE][SIZE]);
int movetiles(int gameboard[SIZE][SIZE], char direction);
void randomtile(int gameboard[SIZE][SIZE]);

int main() {

    srand(time(NULL)); // set seed to NULL for randomness from time.h

    int mainboard[SIZE][SIZE] = {0};

    randomtile(mainboard);
    randomtile(mainboard);

    while (1) {

        printboard(mainboard);

        if (gameover(mainboard)) {

            printf("Game Over!\n");
            break;

        }

        char move = getch_unix();

        if (move == 'q' || move == 'Q') {

            printf("The input scanned is 'q' or 'Q'. Hence Quitting game...\n");
            break;
        }

        if (movetiles(mainboard, move)) {

            randomtile(mainboard);

        }
    }

    return 0;
}