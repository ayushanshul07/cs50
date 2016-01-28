#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int A[10][10] = {0}, cont = 0;
void display()
{
	
	for(int i = 1 ; i < 10 ; ++i)
	{
		for(int j = 1 ; j < 10 ; ++j)
			printf("%d ", A[i][j]);

		printf("\n");
	}
	printf("\n");
}

bool valid(int row , int column , int choice)
{
	for(int i = 0 ; i < 10 ; ++i)
	{
		if(A[row][i] == choice)
			return false;
	}

	for(int i = 0 ; i < 10 ; ++i)
	{
		if(A[i][column] == choice)
			return false;
	}


	int r_box = (row - 1 )/3 ;
	int c_box = (column - 1)/3 ;

	int start_x = (r_box * 3) + 1;
	int start_y = (c_box * 3) + 1;

	for(int i = start_x ; i < start_x + 3 ; ++i)
	{
		for(int j = start_y ; j < start_y + 3 ; ++j)
		{
			if(A[i][j] == choice)
				return false;
		}
	}

	return true;
}

bool check_valid(void)
{
	for (int i = 1; i <= 9; ++i)
	{
		for (int j = 1; j <= 9; ++j)
		{
			if(A[i][j] != 0 && !valid(i, j, A[i][j]))
			{
				return false;
			}
		}
	}
	return true;
}

void solve(int row , int column )
{
	if(row > 9)
		display();

	else if(A[row][column] != 0)
	{
		if(column <  9)
			solve(row , column + 1);
		else
			solve(row + 1 , 1);
	}
	else
	{
		int choice ;
		for(choice = 1 ; choice <= 9 ; choice++)
		{
			if(valid(row , column , choice))
			{
				A[row][column] = choice;
				if(column <  9)
					solve(row , column + 1);
				else
					solve(row + 1 , 1);
			}
		}

		A[row][column] = 0;
	}

}

int main(void)
{
	printf("Give the entries of the 3 X 3 sudoku(solvable) , put 0 inplace of empty spaces\n");
	for(int i = 1 ; i < 10 ; ++i)
	{
		for(int j = 1 ; j < 10 ; ++j)
			scanf("%d", &A[i][j]);
	}

	printf("\n");
	solve(1 , 1);
	printf("\n");
	return 0;
}
