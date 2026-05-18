/*
========================================================================================
 Name        :  balance_bracket.cpp
 Author      :  cdsoftw
 Version     :  1.0
 Course      :  CSCE 3110.001
 Description :  This program uses a STL stack to check a given source code file for un-
		balanced brakets or parentheses.
 Copyright   :  © 2016 CDSoftworks ( AMDG )
========================================================================================
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stack>
using namespace std;

// function prototypes
string getFilename();
void balanceBrackets(stack<char> &b, string fn);

int main (void)
{
	// variable declarations
	stack<char> brackets;
	string filename;
	
	// get the name of the source code file to be analyzed
	filename = getFilename();
	
	// check the code for unbalanced brackets or parentheses
	balanceBrackets(brackets, filename);
	
	return 0;
}

/*
=============================================================================
 Function    :  getFilename
 Parameters  :  none
 Return      :  A string representing the name of a source code file to be
		analyzed.
 Description :  This function uses standard i/o to get the name of a source
		code file from the user.
=============================================================================
*/ 

string getFilename()
{
	// variable declaration
	string fn;
	
	cout << "Enter the filename of the source code to be analyzed: ";
	getline(cin, fn);
	
	return fn;
}

/*
=============================================================================
 Function    :  balanceBrackets
 Parameters  :  stack<char> &b, string fn
 Return      :  none
 Description :  This function reads in a file one line at a time, then loops
		through each line to check for unbalanced brackets or
		parentheses. If unbalanced brackets or parentheses are found,
		the function outputs a meaningful error message and returns
		to main.
=============================================================================
*/ 

void balanceBrackets(stack<char> &b, string fn)
{
	// variable declarations
	ifstream fin;
	string line;
	int lineCount = 1;
	
	// convert fn to a c-string
	char * c_fn = new char [fn.length() + 1];
	strcpy(c_fn, fn.c_str());
	
	cout << "\nOpening file...\n\n";
	
	// open file, check for errors
	fin.open(c_fn);
	if (fin.fail())
	{
		cerr << "ERROR: No such file or directory" << endl;
		exit(EXIT_FAILURE);
	}
	
	cout << "File opened successfully. Checking code for unbalanced brackets or parentheses...\n\n";
	
	while(!fin.eof()) // loop through file, one line at a time
	{
		getline(fin, line);
		
		for (string::iterator it = line.begin(); it != line.end(); ++it) // loop through each line, checking for bracket or parenthesis characters
		{	
			if (*it == '{' || *it == '[' || *it == '(' ) // open bracket or parenthesis found
			{
				b.push(*it); // push onto stack
			}
			
			if (*it == '}') // close curly bracket found
			{
				char temp = b.top();
				b.pop();
				
				if (temp != '{') // brackets don't match
				{
					// print out error message and exit
					cout << "ERROR: unbalanced curly brackets found in line " << lineCount << endl;
					return;
				}
			}
			
			if (*it == ']') // close bracket found
			{
				char temp = b.top();
				b.pop();
				
				if (temp != '[') // brackets don't match
				{
					// print out error message and exit
					cout << "ERROR: unbalanced brackets found in line " << lineCount << endl;
					return;
				}
			}
			
			if (*it == ')') // close parenthesis found
			{
				char temp = b.top();
				b.pop();
				
				if (temp != '(') // parentheses don't match
				{
					// print out error message and exit
					cout << "ERROR: unbalanced parentheses found in line " << lineCount << endl;
					return;
				}
			}
		}
		
		lineCount++;
	}
	
	cout << "Code analysis complete. No unbalanced brackets or parentheses found." << endl;
	
	// close file
	fin.close();
	
	// delete c_fn
	delete[] c_fn;
}
