//Created by Svetleen Guerrier Fall 2016
//Assignment 3 CSCI 235
//Program ADT to solve inputed Sudoku puzzle.
#include "SudokuSolver.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

bool SudokuSolver::readInputFile(string filename)
{
	//Opens file.
	int number=0;
	ifstream gamefile;
	gamefile.open(filename);

	if(gamefile.is_open())
	{
		//Inputs game file to the 2D Array.
		for(int i=1;i<10;i++)
		{
			for(int j=1;j<10;j++)
			{
				gamefile>>number;
				game[i][j]=number;
			}
		}
		return true;
	}
	
	else
		throw PreconditionViolatedException("File did not open"); 
}
bool SudokuSolver::goBack()
{
	//Pop the stack and decrease the Maximum moves everytime finction is called
	if(!stack.IsEmpty())
	{
		stack.Pop();
		MaxMoves--;
		if(MaxMoves<=0)
		{
			//returns false if MMaxMoves reaches to zero.
			return false;
		}
		return true;
	}
	return false;
	//Return false if stack is empty.
}
bool SudokuSolver::remove(int row,int col)
{
	//Intitaizes needed values for the peek 
	//and deletes the (row,Col) that had no common values
	int number=0;
	int item=0;
	game[row][col]=0;
	goBack();
	bool result=false;
	bool stop;

	while(!(stack.IsEmpty())||result==false)
	{
		//Intializes values from peek.
		item=stack.Peek();
		col=item%10;
		item=item/10;
		row=item%10;
		item=item/10;
		number=item%10;
		//If the number is already used and in the array delete number.
		if(game[row][col]==number)
		{
			game[row][col]=0;
			stop=goBack();
			if(stop==false)
				return false;
			
		}
		//Try another number in the spot.
		else
		{
			//Check to see if number will be safe in 2D array
			result=issafe(number,row,col);
			//If true return true.
			if(result==true)
			{
				current_row=row;
				current_column=col;
				return true;
			}
			//Else pop back from stack.
			else
			{
				stop=goBack();
				if(stop==false)
					return false;
			}
		}
	}
	//Returns false if backtracking failed.
	return false;
}
bool SudokuSolver::PutInArray()
{
	if(!(stack.IsEmpty()))
	{
		//Intializes values and puts the values in the game array.
		int item=stack.Peek();
		int column=item%10;
		item=item/10;
		int row=item%10;
		item=item/10;
		int number=item%10;
		game[row][column]=number;
		return true;
	}
	else 
		throw PreconditionViolatedException("Empty Stack called");
}
bool SudokuSolver::insert(int number, int row, int col)
{
	//Puts the number row and column into one integer.
	int concatenate=(number*10+row)*10+col;
	//Puts Integer into array.
	stack.Push(concatenate);
	//Checks to see if the value is safe to put in  the array.
	bool result=issafe(number,row,col);
	return result;
}
bool SudokuSolver::issafe(int number,int row,int col)
{
	//Intializes values and vectors need ed for comparison.
	int box_values=0;
	int col_numbers=0;
	bool result=false;
	int tempo=0;
	int temp=0;
	vector<int>Col_check;
	vector<int>Box_check;
	//Finds the missing numbers in Box and in column
	col_numbers=getMissingInCol(col);
	box_values=getMissingInBox(row,col);
	//Puts the values into vectors.
	while(col_numbers!=0)
	{
		temp=col_numbers%10;
		Col_check.push_back(temp);
		col_numbers=col_numbers/10;
	}
	while(box_values!=0)
	{
		tempo=box_values%10;
		Box_check.push_back(tempo);
		box_values=box_values/10;
	}
	//Compares the number to the box values and column values returnin true 
	//If number is in both vectors.
	for(int i=0;i<Box_check.size();i++)
	{
		if(number==Box_check[i])
		{	
			result=true;
			break;
		}
	}
	for(int i=0;i<Col_check.size();i++)
	{
		if(number==Col_check[i])
			return result;
	}
	return false;
}
int SudokuSolver::nextEmpty()
{
	int i=0;
	for(i=current_column;i<10;i++)
	{	
		//gets the next empty position in row.
		int result=game[current_row][i];
		//returns position if found.
		if(result==0)
			return current_row*i;
	}
	//returns false if at last cell
	if(current_row==9 && i==10)
		return 0;
	//returns -1 if the column is at the end of row.
	else
		return -1;
}
int SudokuSolver::getMissingInBox(int row, int col)
{
	row=row-1;
	col=col-1;
	//Rounds row and column to Box location.
	int new_row = ((row/3)*3);
	int new_col = ((col/3)*3);

	vector<int>numbers;
	int concatenate_Box=0;
	int temp=0;
	//Organizes numbers 1-9 into a number vector.
	for(int i=1;i<10;i++)
	{
		numbers.push_back(i);
	}

	//If number is found indicate that it is not missing
	for(int i=new_row; i < new_row+3; i++)
	{
		for(int j=new_col; j<new_col+3; j++)
		{
			temp=game[i+1][j+1];
			for(int a=0;a<numbers.size();a++)
			{
				if(temp==numbers[a])
				{
					numbers[a]=-1;
				}
			}
		}
	}
	//Puts remaining numbers into integer and returns value
	for(int i=0;i<numbers.size();i++)
	{
		if(numbers[i]!=-1)
		{
			concatenate_Box+=numbers[i];
			concatenate_Box*=10;
		}
	}
	return concatenate_Box/10;
}
int SudokuSolver::getMissingInRow(int row)
{
	vector<int>numbers;
	int concatenate_row=0;
	//Organizes numbers 1-9 into a number vector.
	for(int i=1;i<10;i++)
	{
		numbers.push_back(i);
	}
	//If number is found indicate that it is not missing
	for(int i=1;i<10;i++)
	{
		int temp=game[row][i];

		for(int i=0;i<numbers.size();i++)
		{
			if(temp==numbers[i])
			{
				numbers[i]=-1;
			}
		}
	}
	//Puts remaining numbers into integer and returns value
	for(int i=0;i<numbers.size();i++)
	{
		if(numbers[i]!=-1)
		{
			concatenate_row+=numbers[i];
			concatenate_row*=10;
		}
	}
	return concatenate_row/10;
}
int SudokuSolver::getMissingInCol(int col)
{
	vector<int>numbers;
	int concatenate_col=0;
	int temp=0;
	//Organizes numbers 1-9 into a number vector.
	for(int i=1;i<10;i++)
	{
		numbers.push_back(i);
	}
	//If number is found indicate that it is not missing
	for(int i=1;i<10;i++)
	{
		temp=game[i][col];
		for(int j=0;j<numbers.size();j++)
		{
			if(temp==numbers[j])
			{
				numbers[j]=-1;
			}
		}
	}
	//Puts remaining numbers into integer and returns value
	for(int i=0;i<numbers.size();i++)
	{
		if(numbers[i]!=-1)
		{
			concatenate_col+=numbers[i];
			concatenate_col*=10;
		}
	}
	return concatenate_col/10;
}
bool SudokuSolver::SolvePuzzle(int maxBackSteps)
{
	//Initializes needed values
	int position=0;
	int row_values=0;
	int item=0;
	bool result=true;
	int temp=0;
	//Intializes user inputed backsteps.
	MaxMoves=maxBackSteps;
	//While the backsteps do not equal to or less than zero continue loop
	while(!(MaxMoves<=0))
	{
		//get next empty cell.
		position=nextEmpty();
		//starts new row if it returns -1;
		if(position==-1)
		{
			current_row++;
			current_column=1;
			position=nextEmpty();
		}
		//If there are no more empty cells
		else if(position==0)
			break;
		//Recieve column number by dividing position by column number.
		current_column=position/current_row;
		//gets value missing in row.
		row_values=getMissingInRow(current_row);
		//Tries each value in the cell
		while(row_values!=0)
		{
			item=row_values%10;
			row_values=row_values/10;
			//Inserts value into stack.
			result=insert(item,current_row,current_column);
			//if result is true, put into array.
			if(result==true)
				PutInArray();
		}
		//If no numbers are able to be put into the cell, backtrack.
		if(result==false)
		{
			//when result is equal to true then value is put into array.
			result=remove(current_row,current_column);
			if(result==true)
				PutInArray();
			//else the game is unsolvable when it reaches the MaxBacksteps.
			else
				break;
		}
	}
	if(position==0)
	{
		return true;
	}
	else
		return false;
}
SudokuSolver::SudokuSolver(string filename)
{
	//Intializes where the row and column starts.
	current_row=1;
	current_column=1;
	MaxMoves=0;
	//reads game file.
	readInputFile(filename);
}
void SudokuSolver::DisplayPuzzle()
{
	//shows the maximum moves remaining
	cout<<"Solved with: "<<MaxMoves<<" remaining."<<endl;
	//Displays Sudoku puzzle.
	for(int i=1;i<10;i++)
	{
		for(int j=1;j<10;j++)
		{
			cout<<game[i][j]<<" ";
		}
		cout<<endl;
	}
}













