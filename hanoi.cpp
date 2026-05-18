/*
========================================================================================
 Name        :  hanoi.cpp
 Author      :  cdsoftw
 Version     :  1.0
 Course      :  CSCE 3110.001
 Description :  This program solves the Towers of Hanoi in the minimum number of moves.
 Copyright   :  © 2016 CDSoftworks ( AMDG )
========================================================================================
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stack>
using namespace std;

// create the towers as a global array of stacks
stack<int> towers[3];

// function prototypes
void printTowers();
void makeMove(int tower1, int tower2);

int main (void)
{
	// variable declarations
	int numDisks, moveCount = 1;
	
	// get numDisks
	cout << "***Welcome to Towers of Hanoi 1.0!***" << endl << endl;
	cout << "Enter the number of disks (2 or more): ";
	cin >> numDisks;
	
	if (numDisks < 2)
	{
		cerr << "ERROR: invalid number of disks" << endl;
		exit(EXIT_FAILURE);
	}
	
	// calculate and output minimum number of moves
	const double minMoves = pow(2, numDisks) - 1;
	cout << "The minimum number of moves is: " << minMoves << endl << endl;
	
	// initialize towers
	cout << "Initializing towers..." << endl << endl;
	
	for (int i = numDisks; i > 0; --i)
		towers[0].push(i);
	
	printTowers(); // initial state
	
	if (numDisks % 2 == 0) // even number of disks
	{
		while (towers[2].size() != numDisks) // solve, printing after each move
		{
			cout << "Move #" << moveCount << ": ";
			makeMove(0, 1); // A-B or B-A
			if (moveCount % 10 == 0)
				printTowers();
			else
				cout << endl;
			moveCount++;
			
			// check if done
			if (towers[2].size() == numDisks)
				break;
			
			cout << "Move #" << moveCount << ": ";
			makeMove(0, 2); // A-C or C-A
			if (moveCount % 10 == 0)
				printTowers();
			else
				cout << endl;
			moveCount++;
			
			// check if done
			if (towers[2].size() == numDisks)
				break;
			
			cout << "Move #" << moveCount << ": ";
			makeMove(1, 2); // B-C or B-C
			if (moveCount % 10 == 0)
				printTowers();
			else
				cout << endl;
			moveCount++;
		}
	}
	
	else // odd number of disks
	{
		while (towers[2].size() != numDisks) // solve, printing after each move
		{
			cout << "Move #" << moveCount << ": ";
			makeMove(0, 2); // A-C or C-A
			if (moveCount % 10 == 0)
				printTowers();
			else
				cout << endl;
			moveCount++;
			
			// check if done
			if (towers[2].size() == numDisks)
				break;
			
			cout << "Move #" << moveCount << ": ";
			makeMove(0, 1); // A-B or B-A
			if (moveCount % 10 == 0)
				printTowers();
			else
				cout << endl;
			moveCount++;
			
			// check if done
			if (towers[2].size() == numDisks)
				break;
			
			cout << "Move #" << moveCount << ": ";
			makeMove(2, 1); // C-B or B-C
			if (moveCount % 10 == 0)
				printTowers();
			else
				cout << endl;
			moveCount++;
		}
	}
	
	printTowers();
	
	return 0;
}

void printTowers()
{
	// make a copy of towers so we don't lose data when printing
	stack<int> towers_copy[3];
	
	for (int i = 0; i < 3; i++)
	{
		towers_copy[i] = towers[i];
	}
	
	// print out the copy of towers
	while (!towers_copy[0].empty() || !towers_copy[1].empty() || !towers_copy[2].empty()) // while there are disks left
	{
		// check each tower for disks; if it has any, print its top and pop
		
		// tower A
		if (!towers_copy[0].empty() && towers_copy[0].size() >= towers_copy[1].size() && towers_copy[0].size() >= towers_copy[2].size())
		{
			cout << towers_copy[0].top() << "\t";
			towers_copy[0].pop();
		}
		
		else
		{
			cout << " \t";
		}
		
		// tower B
		if (!towers_copy[1].empty() && towers_copy[1].size() > towers_copy[0].size() && towers_copy[1].size() >= towers_copy[2].size())
		{
			cout << towers_copy[1].top() << "\t";
			towers_copy[1].pop();
		}
		
		else
		{
			cout << " \t";
		}
		
		// tower C
		if (!towers_copy[2].empty() && towers_copy[2].size() > towers_copy[0].size() && towers_copy[2].size() > towers_copy[1].size())
		{
			cout << towers_copy[2].top() << endl;
			towers_copy[2].pop();
		}
		
		else
		{
			cout << endl;
		}
	}
	
	cout << "-----------------\n"
	     << "A       B       C\n\n";
}

void makeMove(int tower1, int tower2)
{
	int disk; // dummy variable for moving disks
	char tower_1c;
	char tower_2c; // towers stored as letter instead of number
	
	switch (tower1)
	{
		case 0:
			tower_1c = 'A';
			break;
		case 1:
			tower_1c = 'B';
			break;
		case 2:
			tower_1c = 'C';
	}
	
	switch (tower2)
	{
		case 0:
			tower_2c = 'A';
			break;
		case 1:
			tower_2c = 'B';
			break;
		case 2:
			tower_2c = 'C';
	}
	
	if (!towers[tower1].empty() && (towers[tower2].empty() || towers[tower1].top() < towers[tower2].top())) // tower1 NOT empty AND (tower2 is empty OR tower1 -> tower2 is legal)
	{
		// move tower1 -> tower2
		disk = towers[tower1].top();
		cout << "Disk " << disk << " to Tower " << tower_2c << endl;
		towers[tower1].pop();
		towers[tower2].push(disk);
	}
		
	else // tower1 is empty OR tower1 -> tower2 is NOT legal
	{
		// move tower2 -> tower1
		disk = towers[tower2].top();
		cout << "Disk " << disk << " to Tower " << tower_1c << endl;
		towers[tower2].pop();
		towers[tower1].push(disk);
	}
}