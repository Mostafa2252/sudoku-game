/*--------------- --------------- --------------- --------------- ---------------
  ---------------  -----sudoku game with fixed level ------------ ---------------
  --------------- -------Dev:Mostafa Mohamed Younis ------------- ---------------
  --------------- -------Embedded software developer------------- ---------------
  --------------- --------------- --------------- --------------- --------------- */

#include <stdio.h>
#include <stdlib.h>


// Reads row, column and value from the player and validates their ranges.
// row, col : 0 to 8      val : 1 to 9
// Returns 0 if all three inputs are in range, 1 otherwise.
// Note: arr is not used by this function.


char scan_value(char arr[][9],char *row,char *col,char *val )
{
    printf("no.row : ");
    scanf("%d",row);  // get the value of row
    if(*row>8||*row<0)
        return 1;    // not valid row value
    printf("no.col : ");
    scanf("%d",col); // get the value of column
    if(*col>8||*col<0)
        return 1;    // not valid column value
    printf("value : ");
    scanf("%d",val); // get the value of the section
    if(*val>9||*val<=0)
        return 1;    // not valid section value

    return 0;        // the three input is valid
}

/* --------------- --------------- --------------- --------------- --------------- */


// Draws the 9x9 board with colors:
//   yellow  : row and column index labels
//   red     : empty cells (0) that can still be filled
//   default : digits already on the board (given clues and the player's entries)


void print_game(char arr_p[][9])
{
    int i,j;
    printf("\033[0;33m"); // print in yellow color
    printf("     0   1   2   3   4   5   6   7   8   \n");
    printf("\033[0m");  // print in gray color
    printf("--------------------------------------\n");
    for(i=0;i<9;i++)
    {
        printf("\033[0;33m");   // print in yellow color rows and column valid values
        printf(" %d ",i);
        for(j=0;j<9;j++)
        {
            printf("\033[0m");  // reset to default color
            printf("|");
            if(arr_p[i][j]>9)
            {
                printf(" %c ",arr_p[i][j]);
            }
            else
            {
                printf("\033[0;31m");  // print in red empty cell (0) that the player can still fill
                printf(" %d ",arr_p[i][j]);
            }
             printf("\033[0m");
        }
        printf("\n");
        printf("   -----------------------------------");
        printf("\n");
    }
}


/* --------------- --------------- --------------- --------------- --------------- */


// Checks whether the player's move is allowed.
// Returns 1 if the cell is already filled (clue or earlier entry),
//   or the value already exists in the same column or row.
// Returns 0 if the move is allowed.
// Note: the 3x3 box is not checked.


char check_value(char arr_p[][9],char row, char col ,char val )
{
    int i;
    if(arr_p[row][col]>9)  // check the section that user access
        return 1;
    else
    {
        val=val+'0';       // assigned the section value to a character
        for(i=0; i<9; i++)  // check that the value is not repeated in the same column
        {
            if(val==arr_p[i][col])
                return 1;       // means wrong answer
        }
        for(i=0; i<9; i++)   // check that the value is not repeated in the same row
        {
            if(val==arr_p[row][i])
                return 1;        // means wrong answer
        }
         return 0;               // correct answer
    }
}



/* --------------- --------------- --------------- --------------- --------------- */

// Returns 1 if the board has no empty cells (0), meaning the player won.
// Every move is validated when entered, so a full board is a correct solution.
// Returns 0 if at least one cell is still empty.


char check_win(char arr_p[9][9])
{
    int i,j;
    for(i=0;i<9;i++) // scan every cell for an empty one (0)
    {
        for(j=0;j<9;j++)
        {
            if(arr_p[i][j]==0)
            {
                return 0;  // still not win
            }
        }
    }
    return 1;  //win
}


/* --------------- --------------- --------------- --------------- --------------- */

// Prints the WINNER banner and asks what to do next.
// Returns the player's choice: 1 = new game, 2 = end the game.


int winner(void)
{
    int num =1;

    printf("\033[0;32m");   // green
    printf("\n");
    printf("   +==========================================+\n");
    printf("   |                                          |\n");
    printf("   |              W I N N E R !               |\n");
    printf("   |                                          |\n");
    printf("   |      *** YOU SOLVED THE SUDOKU ***       |\n");
    printf("   |                                          |\n");
    printf("   +==========================================+\n");
    printf("\033[0m");      // reset to default color

    printf("\n   1 - new game\n");
    printf("   2 - end the game\n");
    printf("   enter the number : ");
    // read the player's choice; main() exits only if it is 2,
    // so any other number (or invalid input) starts a new game
    scanf("%d",&num);
   return num;
}





