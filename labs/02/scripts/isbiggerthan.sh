#! /bin/bash

if [ -z $1 ] || [ -z $2 ]  #if there is no argument
  then 
    echo "ERROR: Require path and size" 
    exit 2

elif [ "$1" -ne "$1" ]
  then  
    echo "ERROR: Did not recieve a number for size"
   exit 3

elif [ "$1" -lt 0 ] 
    then
    echo "ERROR: Recieved a negative number for size"
    exit 4

elif     [ ! -e $2 ]
    then
    echo "ERROR: File does not exits"
    exit 5
fi    

sizeInQuestion=$1
filesize=$(ls -l $2 | cut -d " " -f 5)

if [ $sizeInQuestion -gt $filesize ]
    then 
      echo "no"
      exit 1
else 
    echo "yes"
    exit 0
fi