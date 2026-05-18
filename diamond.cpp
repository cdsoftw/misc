/*
============================================================================
 Name        : diamond.cpp
 Author      : cdsoftw
 Version     : 1.0
 Copyright   : 2015
 Description : Uses 3 programmer-defined functions to determine if an integer
 	       input by the user is an odd number in the range 1 to 19; if the
 	       integer is valid, calculate the sum of all integers from 1 to the
 	       chosen integer; and print out a diamond shape to the screen con-
 	       sisting of x rows of a printable character input by the user,
 	       where x is the chosen integer.
============================================================================
*/

#include <iostream>
using namespace std;

//declaration of functions
bool valid(int odd_num);
int sum(int odd_num);
void diamond(int odd_num, char ch);

int main ( )
{	
	cout << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n"
	     << "|       Computer Science and Engineering        |\n"
         << "|        CSCE 1030 - Computer Science I         |\n"
         << "|  Cole Dapprich  cwd0042  cwd0042@my.unt.edu   |\n"
         << "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+\n";
	
	//odd number between 1 and 19 input by the user 
	int odd_num;
	//boolean value that determines whether or not the number imput by the user follows the required parameters
	bool t_f;
	//sum of all integers from 1 to odd_num
	int result;
	//printable character input by the user to draw a diamond
	char ch;

	/* do-while loop that reads in odd_num and checks to see if it is valid, displaying an error message and re-
	prompting if it isn't and displaying result and exiting the loop if it is*/
	do
	{
		cout << "Please enter an ODD integer in the range 1 to 19: ";
		cin >> odd_num;

		t_f = valid(odd_num);

		if (t_f == false)
		{
			cout << "The number you entered is not valid." << endl;
		}

		else
		{
			result = sum(odd_num);
			cout << "The sum of all integers from 1 to " << odd_num << " is: " << result << endl;
		}

	} while (t_f == false);

	//reads in a printable character to print a diamond
	cout << "Please enter a printable character to draw a diamond: ";
	cin >> ch;

	//calls the void function that draws the diamond
	diamond(odd_num, ch);

	return 0;
}

/*
============================================================================
 Function    : valid
 Parameters  : an odd integer between 1 and 19 input by the user
 Return      : a boolean value representing valid and invalid
 Description : This function determines whether odd_num follows the required
	       parameters.
============================================================================
*/
bool valid(int odd_num)
{
	//if-else statement that returns true if the number is valid and false if it is not
	if ((odd_num >= 1) && (odd_num <= 19) && ((odd_num % 2) == 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
============================================================================
 Function    : sum
 Parameters  : an odd integer between 1 and 19 input by the user
 Return      : an integer representing the sum of all integers from 1 to the
	       parameter.
 Description : This function calculates the sum of all integers from 1 to
	       odd_num using the mathematical formula.
============================================================================
*/
int sum(int odd_num)
{
	//initialization and declaration of the integer sum using the mathmatecial formula
	int sum = (odd_num * (odd_num + 1)) / 2;

	return sum;
}

/*
=============================================================================
 Function    : diamond
 Parameters  : an odd integer between 1 and 19 input by the user and a print-
	       able character input by the user.
 Return      : none
 Description : This function outputs to the screen a diamond of odd_num rows
	       using the printable character input by the user.
=============================================================================
*/
void diamond(int odd_num, char ch)
{
	using namespace std;

	//declaration of counters in for loops
	int row_count, sp_count, ch_count;	
	int odd_count = odd_num - 1;

	//draws the top half of the diamond
	for (row_count = 0; row_count < (odd_num / 2.0); row_count++)
	{
		//outputs the correct number of spaces in each line
		for (sp_count = (odd_num / 2); sp_count > row_count; sp_count--)
		{
			cout << " ";
		}
		
		//outputs the correct number of characters in each line
		for (ch_count = 0; ch_count < (odd_num - odd_count); ch_count++)
		{
			cout << ch;
		}
		
		//updates the counter used to output the characters
		odd_count -= 2;

		cout << endl;
	}

	//(re-)declares and initializes the counters used in both nested loops
	odd_count = odd_num - 1;
	int odd_count2 = 2;

	//draws the bottom half of the diamond
	for (row_count = 0; row_count < (odd_num / 2); row_count++)
	{
		//outputs the correct number of spaces in each line
		for (sp_count = 0; sp_count < (odd_num - odd_count); sp_count++)
		{
			cout << " ";
		}

		//outputs the correct number of characters in each line
		for (ch_count = 0; ch_count < (odd_num - odd_count2); ch_count++)
		{
			cout << ch;
		} 
		
		//updates the counters used in both nested loops
		odd_count--;
		odd_count2 += 2;

		cout << endl;
	}
	
	return;
}
