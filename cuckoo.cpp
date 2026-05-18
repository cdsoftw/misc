/*
========================================================================================
 Name        :  cuckoo.cpp
 Author      :  cdsoftw
 Version     :  1.0
 Course      :  CSCE 3110.021
 Description :  This program reads in a series of integers from a file and uses cuckoo
		hashing to store them in d unique hash tables, where d is provided by
		the user at the program's launch.
 Copyright   :  © 2016 CDSoftworks ( AMDG )
========================================================================================
*/

#include <iostream>	// cin, cout
#include <fstream>	// ifstream, open(), close()
#include <vector>	// vector<int>, push_back(), vector<int>::iterator, begin(), end()
#include <cstdlib>	// exit(), EXIT_FAILURE
#include <cmath>	// sqrt()
using namespace std;

static int tableSize = 11; // the initial table size, stored as a global variable

// function prototypes
void readFile(int **arr, int numTables);
int hash(int num);
bool find(int **arr, int numTables, int num);
void place(int **arr, int numTables, int num);
void rehash(int **arr, int numTables);
bool isPrime(int num);

int main (void)
{
	// variable declarations
	int **tables;
	int numTables;
	
	while (1) // loop indefinitely
	{
		// get the number of tables from the user
		cout << "Enter the number of hash tables to use (2 or more): ";
		cin >> numTables;
		
		if (numTables >= 2) break; // exit loop
		
		cout << "Invalid number of tables entered. ";
	}
	
	cout << "\nCreating hash tables...\n\n";
	
	// create hash tables
	tables = new int *[numTables];
	
	for (int i = 0; i < numTables; i++)
	{
		tables[i] = new int[tableSize];
	}
	
	// initialize hash tables
	for (int i = 0; i < numTables; i++)
	{
		for (int j = 0; j < tableSize; j++)
		{
			tables[i][j] = -1;
		}
	}
	
	cout << "Hash tables created.\n\n";
	
	// read in file and hash
	readFile(tables, numTables);
	
	cout << "Hashing complete. Final table size is: " << tableSize << endl << endl;
	
	// delete tables
	for (int i = 0; i < numTables; i++)
	{
		delete [] tables[i];
	}
	
	delete [] tables;
	
	return 0;
}

// calculates the key using division hashing

int hash(int num)
{
	return num % tableSize;
}

// returns true if a number passed in is in the tables, false otherwise

bool find(int **arr, int numTables, int num)
{
	for (int i = 0; i < numTables; i++)
	{
		for (int j = 0; j < tableSize; j++)
		{
			if (arr[i][j] == num) return true;
		} // for
	} // for
	
	return false;
} // find

// reads in numbers from the file, calling the placement function if the tables do not already contain the number

void readFile(int **arr, int numTables)
{
	// variable declarations
	ifstream fin;
	int num, numCount = 0;
	
	cout << "Opening \"raw_int.txt\"...\n\n";
	
	// open file, check for errors
	fin.open("raw_int.txt");
	if (fin.fail())
	{
		cerr << "ERROR: No such file or directory" << endl;
		exit(EXIT_FAILURE);
	}
	
	cout << "File opened successfully. Reading in numbers and hashing...\n\n";
	
	while (!fin.eof()) // Read in number, call placement function
	{
		fin >> num;
		if(!find(arr, numTables, num)) // num is not in any table
		{
			// attempt to place num in a table
			place(arr, numTables, num);
		}
	}
	
	// close file
	fin.close();
}

// places the number in the appropriate table according to the cuckoo hashing algorithm, rehashing if necessary

void place(int **arr, int numTables, int num)
{
	// variable declarations
	int temp[numTables - 1];
	int key, i = 0, j = 0;
	
	// evaluate hashing function
	key = hash(num);
	
	if (arr[0][key] == -1) // bucket is empty in table A
	{
		// place num in table A
		cout << num << " goes in table 1 slot " << key << endl;
		arr[0][key] = num;
	}
	
	else // bucket is full in table A
	{	
		while (i < numTables) // attempt to resolve collision
		{
			// get value from table i
			temp[j] = arr[i][key];
			
			// update counters
			i++;
			j++;
			
			if (i < numTables && arr[i][key] == -1) // bucket is empty in the next table
			{
				// place temporary variables in tables B - i and num in table A, exit loop
				for (int k = i; k > 0; k--)
				{
					cout << "Moving " << temp[k - 1] << " to table " << k + 1 << " slot " << key << endl;
					arr[k][key] = temp[k - 1];
				}
				
				cout << num << " goes in table 1 slot " << key << endl;
				arr[0][key] = num;
				break;
			}
		}
	}
	
	// check for cycles of insertion and displacement
	if (!find(arr, numTables, num)) // placement unsuccessful, meaning the bucket is occupied in all tables
	{
		// output info, rehash, and try again
		cout << "\nREHASHING: all buckets with key " << key << " are full.\n";
		rehash(arr, numTables);
		place(arr, numTables, num);
	}
	
	// check load factors
	for (int k = 0; k < numTables; k++)
	{
		double count = 0.0;
		
		for (int l = 0; l < tableSize; l++)
		{
			if (arr[k][l] != -1) // count all values in current table
			{
				count += 1.0;
			}
		}
		
		// calculate load factor
		double lf = count / tableSize;

		if (lf > 0.5)
		{
			// rehash, output info, exit loop
			cout << "\nREHASHING: Table " << k + 1 << " has a load factor greater than 0.5\n";
			rehash(arr, numTables);
			break;
		}
	}
}

// returns true if a number passed in is prime, false otherwise

bool isPrime(int num)
{
	double squareroot = sqrt(num);
	int int_sqrt = squareroot;
	
	if (squareroot / int_sqrt == 1.0) // squareroot is an int
	{
		return false;
	}

	else // squareroot is a double
	{
		for (int i = 2; i < squareroot; i++)
		{
			if (num % i == 0) // num is divisible by a number besides itself and 1
			{
				return false;
			}
		} 
	}

	return true;
}

void rehash(int **arr, int numTables)
{
	// store all the values from the hash tables in a vector
	vector<int> tableValues;
	double count = 0.0;
	
	for (int i = 0; i < numTables; i++)
	{
		for (int j = 0; j < tableSize; j++)
		{
			tableValues.push_back(arr[i][j]);
		}
	}
	
	// double the size and find the closest prime above it
	int newSize = tableSize * 2;
	
	while (!isPrime(newSize))
	{
		newSize++;
	}
	tableSize = newSize; // resize the tables
	
	// delete columns of old array
	for (int i = 0; i < numTables; i++)
	{
		delete [] arr[i];
	}
	
	// create new columns
	for (int i = 0; i < numTables; i++)
	{
		arr[i] = new int[tableSize];
	}
	
	// initialize new tables
	for (int i = 0; i < numTables; i++)
	{
		for (int j = 0; j < tableSize; j++)
		{
			arr[i][j] = -1;
		}
	}
	
	for (vector<int>::iterator it = tableValues.begin(); it != tableValues.end(); ++it)
	{
		place(arr, numTables, *it);
	}
	
	cout << "\nNew table size: " << tableSize << endl;
	
	// print new load factors
	for (int i = 0; i < numTables; i++)
	{
		double count = 0.0;
		
		for (int j = 0; j < tableSize; j++)
		{
			if (arr[i][j] != -1) // count all values in current table
			{
				count += 1.0;
			}
		}
		
		// print new load factors
		double lf = count / tableSize;

		cout << "Table " << i + 1 << "'s load factor is: " << lf << endl;
	}
	
	cout << endl;
}