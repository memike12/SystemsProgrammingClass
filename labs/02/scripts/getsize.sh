#! /bin/bash

if [ -z $1 ]  #if there is no argument
  then 
    echo "ERROR: require file"  1>&2
elif [ ! -e $1 ]  # if the argument is not a file
   then 
    echo "ERROR: File $1 does not exist" 1>&2
elif [ -e $1 ] #if it exists then print it's size
   then ls -l $1 | cut -d " " -f 5
fi