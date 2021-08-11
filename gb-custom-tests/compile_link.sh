#!/bin/bash

if [ -z $1 ]; 
then
	echo "Error: requires 1 argument"
	exit 0
fi

FILE_1=$1
FILE_1_LEN=${#FILE_1}
FILE_BASE=${FILE_1:0:(($FILE_1_LEN-4))}
FILE_2="$FILE_BASE.o"
FILE_3="$FILE_BASE.gb"

rgbasm -L -o $FILE_2 $FILE_1
rgblink -o $FILE_3 $FILE_2
rgbfix -v -p 0xFF $FILE_3
