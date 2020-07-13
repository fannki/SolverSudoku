#include <stdio.h>

//sudoku problem (transcribe your problem into cells, if the cell is an empty, than write "0")
int sudoku_problem[9][9] = {0,0,0, 0,3,0, 0,8,6,
    						0,3,0, 5,0,0, 7,0,0,
    						0,0,4, 0,8,0, 0,0,9,
    
    						0,0,3, 0,0,0, 0,2,7,
    						0,1,0, 3,0,4, 0,6,0,
							5,4,0, 0,0,0, 9,0,0,
    
    						4,0,0, 0,7,0, 6,0,0,
    						0,0,1, 0,0,2, 0,7,0,
    						3,2,0, 0,4,0, 0,0,0};

//function to print sudoku problem in console
void print_problem()
{
	int i, j;										//i - row, j - column
    printf("This is your sudoku problem: \n");		//explanation
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");	//first make a horizontal line
	for(i = 0; i < 9; i++)							//cycle by rows
	{	
		printf("|");								//make a vertical line at the beginning of each line
		for(j = 0; j < 9; j++)						//cycle by columns
		{
			printf(" %d ", sudoku_problem[i][j]);
			if(((j + 1) % 3) == 0)					//after every third column of numbers make a vertical line	
			{
				printf("|");
			}
		}
		printf("\n");
		if (((i + 1) % 3) == 0)						//when the rows are finished, make a horizontal line
		{
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		}
	}
}

//function to print solve sudoku after solve_sudoku function
void print_sudoku()
{
    int i, j;										//i - row, j - column
    printf("\nThis is your solve sudoku:\n");		//explanation
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");	//first make a horizontal line
	for(i = 0; i < 9; i++)							//cycle by rows
	{	
		printf("|");								//make a vertical line at the beginning of each line
		for(j = 0; j < 9; j++)						//cycle by columns
		{
			printf(" %d ", sudoku_problem[i][j]);
			if(((j + 1) % 3) == 0)					//after every third column of numbers make a vertical line	
			{
				printf("|");
			}
		}
		printf("\n");
		if (((i + 1) % 3) == 0)						//when the rows are finished, make a horizontal line
		{
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		}
	}
}

//function finds a vacant cell and makes the variables ‘row’ and ‘col’ equal to indices of that cell.
int number_empty(int *row, int *col)
{
    int num_empty = 0;
    int i, j;										//i - row, j - column
    for(i = 0; i < 9; i++)							//cycle by rows
    {
        for(j = 0; j < 9; j++)						//cycle by columns
        {
            if(sudoku_problem[i][j] == 0)			//cell is an empty
            {							
                *row = i;							//changing the values of row
                *col = j;							//changing the values of col
                num_empty = 1;						//there is one or more emply cell
                return num_empty;
            }
        }
    }
    return num_empty;
}

//function checks if we can put the value ‘n’ in the cell (r, c and matrix block) or not
int put_values(int n, int r, int c)					//n - value from 1 to 9
{
    int i, j;										//i - row, j - column
    for(i = 0; i < 9; i++)							//checking in row
    {
        if(sudoku_problem[r][i] == n)				//check whether there is a cell with the value "n" in the line "r" or not
        {
            return 0;
        }
    }				
    for(i = 0; i < 9; i++)							//checking in column
    {
        if(sudoku_problem[i][c] == n)				//check whether there is a cell in the value "n" with the column "c" or not
        {
            return 0;
        }
    }
    int row_start = (r/3)*3;						//checking row in matrix block
    int col_start = (c/3)*3;						//checking column in matrix block
    for(i = row_start; i < row_start + 3; i++)
    {
        for(j = col_start; j < col_start + 3; j++)
        {
            if(sudoku_problem[i][j] == n)			//check whether there is a cell in the value "n" with the matrix block 3*3 or not
            {
                return 0;
            }
        }
    }
    return 1;
}

//function to solve sudoku 
int solve_sudoku()
{
    int row;										//row
    int col;										//column
    if(number_empty(&row, &col) == 0)				//if all cells are assigned then the sudoku is already solved
    {
        return 1;
    }
    int n, i;										//i - row, n - value
    for(i = 1; i <= 9; i++)							//cycle by numbers from 1 to 9
    {
        if(put_values(i, row, col))					//if we can assign i to the cell or not   //the cell is sudoku_problem[row][col]
        {
            sudoku_problem[row][col] = i;
            if(solve_sudoku())						//using back track
            {
                return 1;
            }
            else
            {
            	sudoku_problem[row][col] = 0;			//if we can't proceed with this solution - reassign the cell
            }
        }
    }
    return 0;
}

int main()
{
	print_problem();
    if(solve_sudoku())
    {
        print_sudoku();
    }
    else
    {
        printf("\nSorry, but there is no solution :( \nPlease, check the spelling of the problem!\n");
    }
    return 0;
}
