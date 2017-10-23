//Sudoku Solver game main file.
//Created by Svetleen Guerrier Fall 2016.
//CSCI 235 Assignment 3.
//Main File for the Sudoku Solver which tries to solve a file inputed 
//Sudoku in a number of amount of user inputed steps.
#include <iostream>
#include "SudokuSolver.h"
#include <string>
using namespace std;

int main()
{
	//Intializes values
	int steps=0;
	bool result;
	string confirm="";

	//name of puzzle file
	string game="Puzzle.txt";
	SudokuSolver Puzzle(game);

	//user inputs the maximum backsteps they want the game solved in.
	cout<<"Input Maximum steps you want the puzzle to be solved in: ";
	cin>>steps;

	//return true if the game solved in the maximum backsteps.
	result=Puzzle.SolvePuzzle(steps);
	if(result==true)
	{	
		cout<<"Finished Puzzle: "<<endl;
		Puzzle.DisplayPuzzle();
	}

	//User inputs a new number they want the game solved to solved in.
	else
	{
		while(result==false)
		{
			cout<<"Current Puzzle: "<<endl;
			Puzzle.DisplayPuzzle();
			cout<<"Puzzle was not able to solve in inputed max steps would you like to continue?: ";
			cin>>confirm;
			if(confirm=="Yes"||confirm=="yes")
			{
				cout<<"Input new steps: ";
				cin>>steps;
				result=Puzzle.SolvePuzzle(steps);
			}
			else 
				break;
			
		}
		cout<<"Finished Puzzle: "<<endl;
		Puzzle.DisplayPuzzle();
	}
	
	return 0;
}