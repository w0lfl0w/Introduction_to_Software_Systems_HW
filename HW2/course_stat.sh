#!/bin/bash

#check if we got 1 argument, if not exit
if [ "$#" -ne 1 ]; then
    echo "Wrong number of arguments" >&2 
    exit
fi


#exit if we dont have a file in the name of the argument given

if [[ ! -f "$1.txt" ]]; then
    echo "Course not found" >&2
    exit
fi


#delete the folder and all its files if it exists 
if [[ -d "$1_stat" ]]; then
    rm -r ./"$1_stat"
fi

mkdir ./"$1_stat"

#copy only the grades from the given file to /course_stat/grades.txt
awk 'NR!=1{print $2}' "$1.txt" > ./"$1_stat"/grades.txt


#compile the c program
gcc -c -g -Wall calc_statistics.c

gcc -o calc_statistics.exe calc_statistics.o

#run the program
./calc_statistics.exe "./$1_stat/course_statistics.txt" "./$1_stat/grades.txt"

#print the histogram
cat ./"$1_stat"/course_statistics.txt
