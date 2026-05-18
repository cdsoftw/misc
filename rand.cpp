/*
===========================================================================================
 Name        :  rand.cpp
 Author      :  cdsoftw
 Version     :  1.0
 Course      :  CSCE 4444.003
 Description :  This program generates sets of integers that either do not repeat or repeat
                within a limited range, then outputs the integers to file in random order.
 Copyright   :  © 2016 CDSoftworks ( AMDG )
===========================================================================================
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

int main (int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "USAGE: " << argv[0] << " [size] [output_file] OR " << argv[0] << " [size] [range] [output_file]\n\n";
        exit(EXIT_FAILURE);
    }
    
    // variable declarations
    std::vector<int> v;
    std::ofstream fout;
    int size = atoi(argv[1]);
    int range;
    
    if (argc > 3) // range is specified
    {
        range = atoi(argv[2]);
        
        // open file, check for errors
        fout.open(argv[3]);
        if (fout.fail())
        {
            std::cerr << "ERROR: No such file or directory" << std::endl;
            exit(EXIT_FAILURE);
        } // if
    } // if
    
    else // range is not specified
    {
        range = size;
        
        // open file, check for errors
        fout.open(argv[2]);
        if (fout.fail())
        {
            std::cerr << "ERROR: No such file or directory" << std::endl;
            exit(EXIT_FAILURE);
        } // if
    } // if
    
    srand(time(NULL)); // seed prng
    
    if (range == size) // numbers should not repeat
    {
        for (int i = 0; i < size; ++i) v.push_back(i); // initialize vector
        std::random_shuffle(v.begin(), v.end()); // randomize vector
        
        // output randomized vector to file
        for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        {
            fout << *it;
            if (it != v.end() - 1) fout << "\n";
        } // for
    } // if
    
    else // numbers will repeat
    {
        // output random numbers within range to file
        for (int i = 0; i < size; i++)
        {
            int a = rand() % range;
            fout << a;
            if (a != size - 1) fout << "\n";
        } // for
    } // else
    
    // close file
    fout.close();
    
    return 0;
} // main