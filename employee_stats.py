#==========================================================================================
#Name        :  count.py
#Author      :  cdsoftw
#Version     :  1.0
#Course      :  CSCE 4430.001
#Description :  This python script uses a class to parse a .csv file and create a list of
#               employees based on the information it contains. Based on a command line
#               argument, we can sort the employees by last name, calculate each employee's
#               average wage, or find the highest earning employee for each position.
#Copyright   :  Copyright 2016 CDSoftworks ( AMDG )
#==========================================================================================

import csv
import sys


class Employee:

    def __init__(self, filename="employee.csv"):
        # Filename
        self.filename = filename
        # Data from the csv
        self.data = [x for x in csv.reader(open(filename))]

    def sortLastName(self, reverse=False):
        return sorted(map(lambda x: x[0], self.data[2:]), reverse=reverse, key=lambda x: x.split()[1])
    def averageWage(self):
        names = []
        hours = []
        wages = [] 
        avgWages = [] #empty lists
        
        #parse csv file
        for i in self.data[2:]:
            names.append(i[0])
            hours.append(int(i[4]) + int(i[5]) + int(i[6]) + int(i[7]) + int(i[8]))
            wages.append(float(i[3]))
        
        #calculate wages and print
        for i in range(len(names)):
            avgWages.append(round(hours[i] * wages[i] / 5.0, 2))
            print names[i], " - ", avgWages[i]
    def highestEarning(self):
        names = [[] for i in range(3)]
        EPIDs = [[] for i in range(3)]
        hours = [[] for i in range(3)]
        wages = [[] for i in range(3)]
        earnings = [[] for i in range(3)] #empty nested lists
        
        #parse csv file
        for i in self.data[2:]:
            if i[1] == "Entry Level":
                names[0].append(i[0])
                EPIDs[0].append(i[2])
                hours[0].append(int(i[4]) + int(i[5]) + int(i[6]) + int(i[7]) + int(i[8]))
                wages[0].append(float(i[3]))
            elif i[1] == "Middle Level":
                names[1].append(i[0])
                EPIDs[1].append(i[2])
                hours[1].append(int(i[4]) + int(i[5]) + int(i[6]) + int(i[7]) + int(i[8]))
                wages[1].append(float(i[3]))
            elif i[1] == "Senior Level":
                names[2].append(i[0])
                EPIDs[2].append(i[2])
                hours[2].append(int(i[4]) + int(i[5]) + int(i[6]) + int(i[7]) + int(i[8]))
                wages[2].append(float(i[3]))
            else:
                print "ERROR: Unknown employee position. Expected: Entry Level, Middle Level, or Senior Level"
                return
        
        #calculate earnings for each group
        for i in range(len(names[0])):
            earnings[0].append(round(hours[0][i] * wages[0][i], 2))
        for i in range(len(names[1])):
            earnings[1].append(round(hours[1][i] * wages[1][i], 2))
        for i in range(len(names[2])):
            earnings[2].append(round(hours[2][i] * wages[2][i], 2))
        
        #find max earning for each group
        max0 = max(earnings[0])
        max1 = max(earnings[1])
        max2 = max(earnings[2])
        
        #find name of employee with max earning for each group
        for i in range(len(names[0])):
            if earnings[0][i] == max0:
                print names[0][i], " - Entry Level - ", EPIDs[0][i]
        for i in range(len(names[1])):
            if earnings[1][i] == max1:
                print names[1][i], " - Middle Level - ", EPIDs[1][i]
        for i in range(len(names[2])):
            if earnings[2][i] == max2:
                print names[2][i], " - Senior Level - ", EPIDs[2][i]

def main():
    #check number of args, get choice
    if len(sys.argv) < 2:
        print 'ERROR: Not enough arguments'
        sys.exit(2)
    choice = sys.argv[1]
    
    #parse csv, create employees
    empl = Employee()
    
    #call appropriate function
    if choice == "1":
        sortedList = empl.sortLastName()
        for i in sortedList:
            print i
    elif choice == "2":
        empl.averageWage()
    elif choice == "3":
        empl.highestEarning()
    else:
        print 'ERROR: Invalid argument'
        sys.exit(2)
    
if __name__ == "__main__":
    main()