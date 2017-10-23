//Created by Svetleen Guerrier Fall 2016
//Assignment 3 CSCI 235
//Linked list of Stack
#ifndef TEACH_CSCI235_STACKADT_SuDOKUSOLVER_H
#define TEACH_CSCI235_STACKADT_SuDOKUSOLVER_H

#include "StackInterface.h"	//for stack
#include "Node.h"			//for linked list
#include "PreconditionViolatedException.h"	//for exceptions
#include "LinkedStack.h"


class SudokuSolver
{
private:
	//Pre:Recieves number option along with row and column number.
	//Post:Concatenates the numbers, puts them in an integer then puts in stack. 
	//Returns whether combination is safe to put in the arrsy.
	bool insert(int number,int row, int col);
	//Pre:Recieves Row and Column number to remove to start backstracking
	//Post:Deletes row and column number in stack and in array if it violates any conditions and sets new current column and current row.
	bool remove(int row, int col);
	//Pre:Member variable stack
	//Post:Deletes the last input in stack and decreases MaxMoves.
	bool goBack();
	//Pre:Searches member variable array
	//Post:returns position of the next zero or returns zero if there is none
	int nextEmpty();
	//Pre:Recieves row and column number
	//Post:Rounds off to a box then returns missing numbers in the box
	int getMissingInBox(int row, int col);
	//Pre:recieves row number to search
	//Post:returns numbers that are missing in the row.
	int getMissingInRow(int row);
	//Pre:recieves column number
	//Post:Returns columns that are missing in the column number.
	int getMissingInCol(int col);
	//Pre:recieves file name
	//Post:opens file and pus data into a 3d array
	bool readInputFile(string filename);
	//Pre:Member stack
	//Post:Peek Stack Seperates values and puts the value in an array.
	bool PutInArray();
	//Pre:recieves proposed number row and column
	//Post:Checks to see if putting the number does not violate game rules. Returns either true or false.
	bool issafe(int number,int row,int col);
	//Data 2d array
	int game[10][10];
	//Maximum moves user inputed
	int MaxMoves;
	//Row game is currently on.
	int current_row;
	//Column game is currently on.
	int current_column;
	//List which holds all the optional rows,columns and number.
	LinkedStack<int> stack;
public:
	//Intializes values and starts the input of filename
	SudokuSolver(string filename);
	//Driver of the puzzle returns true if the game is solved within maxsteps otherwise return false.
	bool SolvePuzzle(int maxBackSteps);
	//Displays current stage of puzzle.
	void DisplayPuzzle();
};
#include "SudokuSolver.cpp"
#endif