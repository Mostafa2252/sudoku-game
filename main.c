/*--------------- --------------- --------------- --------------- ---------------
  ---------------  -----sudoku game with fixed level ------------ ---------------
  --------------- -------Dev:Mostafa Mohamed Younis ------------- ---------------
  --------------- -------Embedded software developer------------- ---------------
  --------------- --------------- --------------- --------------- --------------- */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mmsystem.h>
#include <string.h>

// Function prototypes (defined in sudoku.c)


char check_value(char arr_p[][9],char row, char col ,char val );
char scan_value(char arr[][9],char *row,char *col,char *val );
void print_game(char arr_p[][9]);
char check_win(char arr_p[9][9]);
int winner(void);




int main()
{
    // Fixed puzzle (never modified). 0 = empty cell, '1'-'9' = given clues stored as ASCII characters
    const char arr_c [9][9] = {{'1','2',0,'8',0,'6',0,0,'9'},
        {0,0,'6',0,'7','1','8','2','3'},
        {'7',0,0,0,'4',0,0,0,'5'},
        {'6','7','1',0,'2','3',0,0,'8'},
        {'3',0,'5',0,0,0,'2','1',0},
        {0,'4',0,'1','9',0,'6','3',0},
        {0,'6',0,0,'3',0,0,'5',0},
        {'9',0,'7',0,0,0,'3',0,'2'},
        {'5',0,0,0,'1','9',0,'8','6'}};


    // Working copy of the puzzle that the player edits
    char arr_p [9][9];


    /* --------------- --------------- --------------- --------------- --------------- */
    //  Test board (nearly solved) to check the win condition quickly. Comment out the real arr_c above and uncomment this one to use it.
     //const char arr_c [9][9] = {{'1','2','3','8','5','6','4','7','9'},{'4','5','6','9','7','1','8','2','3'},{'7','8','9','3','4','2','1','6','5'},{'6','7','1','4','2','3','5','9','8'},{'3','9','5','6','8','7','2','1','4'},{'2','4','8','1','9','5','6','3','7'},{'8','6','2','7','3','4','9','5','1'},{'9','1','7','5','6','8','3','4','2'},{'5',0,0,0,'1','9','0','8','6'}};
    /* --------------- --------------- --------------- --------------- ---------------*/



    // Heap variables that receive the player's input (value, row, column); passed to scan_value by pointer
    char*val = (char*)malloc(1);
    char*row = (char*)malloc(1);
    char*col = (char*)malloc(1);

    // Loop flag: 1 = keep playing, 0 = exit the program
    int playAgain = 1;


    while(playAgain)
    {
        system("cls");   // clear the console (Windows only)
        memcpy(arr_p, arr_c, sizeof(arr_p));   // Reset the board to the original puzzle (start of every new game)

        // One round: repeat until the board is full
        while(1)
        {
            print_game(arr_p); // draw the board

                //Note : wav files must be in the working directory; link with -lwinmm
            if(scan_value(arr_p,row,col,val)) // invalid input (row/col/value out of range)
            {
                // user input a not valid number of row,column or value
                // the range of number is from (0 to 8)
                PlaySound(TEXT("wrong.wav"),NULL,SND_ASYNC);  // play the error sound (async)
            }
            else     // input is in range, now check the move itself
            {

                if(check_value(arr_p,*row,*col,*val))   // returns 1 if the cell is locked or the value already exists in its row/column
                {
                    PlaySound(TEXT("wrong.wav"),NULL,SND_ASYNC);  // play the error sound (async)
                }
                else
                {
                    // store the digit as an ASCII character; non-zero cells are treated as locked, so it can't be overwritten
                    arr_p[*row][*col]=*val+'0';
                    PlaySound(TEXT("correct.wav"),NULL,SND_ASYNC); // play correct sound (async)
                }
            }


            if(check_win(arr_p))  // the board has no empty cells, so the player has won
            {
                PlaySound(TEXT("win.wav"),NULL,SND_ASYNC);  //voice function winner sound
                system("cls");
                if(winner()== 2) // player chose "end the game"; any other choice starts a new game
                    playAgain = 0;
                break;       // leave the round loop; the outer loop restarts or exits
            }
            system("cls");

        }
    }

    // Free the heap memory before the program exits
    free(val);
    free(row);
    free(col);


    return 0;
}
