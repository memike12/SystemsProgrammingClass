#!/bin/bash

#TODO: Complete bash program	
for arg in $*
do
    $?=$(./isnumber $arg)
    if [ "$?" = "0" ]
    then
        echo "$arg"
    fi
 
done

./
