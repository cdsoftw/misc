#=========================================================================================
#Name        :  count.py
#Author      :  cdsoftw
#Version     :  1.0
#Course      :  CSCE 4430.001
#Description :  This python script reads in two command line arguments and counts all occ-
#               urrences of the second argument in the file indicated by the first.
#Copyright   :  Copyright 2016 CDSoftworks ( AMDG )
#=========================================================================================

from sys import argv, exit

#check number of args
if len(argv) < 3:
    print 'ERROR: Not enough arguments'
    exit(2)

#get command line args
filename = argv[1]
str = argv[2]

#count str in file
file = open(filename).read()
count = file.count(str)
print count