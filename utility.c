// CODE: Inlcude necessary librar(y/ies)
#include <termios.h> // used in getch_unix()
#include <unistd.h>  // used in getch_unix()
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include "utility.h"

#define SIZE 4

// CODE: Declare necessary functions and related variables

// CODE: the implementation of functions and related variables 


/*Receiving an input from keyboard
IMPORTANT: DO NOT CHANGE ANYTHING IN getch_unix() FUNCTION.
To test this function and see if it works on your OS you can use testMyInput.c. 
It should work on any UNIX based OS.
This function receives all possible charaters from a keyboard.
The returned character `ch` will be used in "your game logic" as:
if ch='w' // Move Up
if ch='s' // Move Down
if ch='a' // Move Left
if ch='d' // Move Right
if ch='q' // break the game loop and quit
otherwise  do nothing
*/
char getch_unix() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Gets the current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


// Function to print the board:
void printboard(int gameboard[SIZE][SIZE]) {
    printf("\n  2048 GAME STARTS \n");
    printf("Press 'w' to move up\n");
    printf("Press 's' to move down\n");
    printf("Press 'a' to move left\n");
    printf("Press 'd' to move right\n");
    printf("Press 'q' to quit\n\n");

    // Print the board
    for (int i = 0; i < SIZE; i++) {

        // Print each row
        for (int j = 0; j < SIZE; j++) {
            if (gameboard[i][j] == 0) {
                printf(".   ");  // Align empty spaces
            } else {
                printf("%-3d ", gameboard[i][j]); // Left-align numbers
            }
        }
        printf("\n");
    }
}



// Function to place a random tile (2 or 4) in an empty space
void randomtile(int gameboard[SIZE][SIZE]){
    int box[SIZE * SIZE][2], count = 0;

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (gameboard[i][j] == 0){
                box[count][0] = i;
                box[count][1] = j;
                count++;
            }
        }
    }
    
    if (count > 0){
        int randomindex = rand() % count;
        int rows = box[randomindex][0];
        int columns = box[randomindex][1];
        gameboard[rows][columns] = ((rand() % 2) + 1) * 2;
    }
}


// Function to move and merge tiles
int movetiles(int gameboard[SIZE][SIZE], char direction){
    int movedtile = 0;
    int testboard[SIZE][SIZE];
    int merged[SIZE][SIZE] = {0};
    
    // Copy board to temp_board for checking movement
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            testboard[i][j] = gameboard[i][j];

    
    // Move logic for each direction
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){

            
            if ((direction == 'a' || direction == 'A') && j > 0){ // Move left

                for (int k = j; k > 0; k--){
                    if (gameboard[i][k - 1] == 0){
                        gameboard[i][k - 1] = gameboard[i][k];
                        gameboard[i][k] = 0;
                    } else if (gameboard[i][k - 1] == gameboard[i][k] && !merged[i][k - 1]){
                        gameboard[i][k - 1] *= 2;
                        gameboard[i][k] = 0;
                        merged[i][k - 1] = 1;
                        movedtile = 1;
                        break;
                    }
                }
            }


            if ((direction == 'w' || direction == 'W') && i > 0){ // Move up

                for (int k = i; k > 0; k--){
                    if (gameboard[k - 1][j] == 0) {
                        gameboard[k - 1][j] = gameboard[k][j];
                        gameboard[k][j] = 0;
                        movedtile = 1;
                    } else if (gameboard[k - 1][j] == gameboard[k][j] &&  !merged[k - 1][j]){
                        gameboard[k - 1][j] *= 2;
                        gameboard[k][j] = 0;
                        merged[k - 1][j] = 1;
                        movedtile = 1;
                        break;
                    }
                }
            }


            if ((direction == 's' || direction == 'S') && i < SIZE - 1){ // Move down

                for (int k = i; k < SIZE - 1; k++){
                    if (gameboard[k + 1][j] == 0){
                        gameboard[k + 1][j] = gameboard[k][j];
                        gameboard[k][j] = 0;
                        movedtile = 1;
                    } else if (gameboard[k + 1][j] == gameboard[k][j] && !merged[k + 1][j]){
                        gameboard[k + 1][j] *= 2;
                        gameboard[k][j] = 0;
                        merged[k + 1][j] = 1;
                        movedtile = 1;
                        break;
                    }
                }
            }


            if ((direction == 'd' || direction == 'D') && j < SIZE - 1){ // Move right

                for (int k = j; k < SIZE - 1; k++){
                    if (gameboard[i][k + 1] == 0) {
                        gameboard[i][k + 1] = gameboard[i][k];
                        gameboard[i][k] = 0;
                        movedtile = 1;
                    } else if (gameboard[i][k + 1] == gameboard[i][k] && !merged[i][k + 1]){
                        gameboard[i][k + 1] *= 2;
                        gameboard[i][k] = 0;
                        merged[i][k + 1] = 1;
                        movedtile = 1;
                        break;
                    }
                }
            }
        }
    }
    

    // Check if board has changed
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (testboard[i][j] != gameboard[i][j])
                movedtile = 1;
    
    return movedtile;
}


// Function to check if the game is over 
int gameover(int gameboard[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) { 
            if (gameboard[i][j] == 0) return 0;
            if (j < SIZE - 1 && gameboard[i][j] == gameboard[i][j + 1]) return 0;
            if (i < SIZE - 1 && gameboard[i][j] == gameboard[i + 1][j]) return 0;

        }
    }
    return 1;
}