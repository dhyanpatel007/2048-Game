#ifndef UTILITY_H
#define UTILITY_H

#define SIZE 4
char getch_unix();

void printboard(int gameboard[SIZE][SIZE]);
int movetiles(int gameboard[SIZE][SIZE], char direction);
void randomtile(int gameboard[SIZE][SIZE]);
int gameover(int gameboard[SIZE][SIZE]);

#endif
