#!/bin/bash

echo "Hello $USER"

if [ $HOME == $PWD ]
then
    echo "Good, you're in your home directory: $HOME"
else
    echo "What are you doing away from home?!?"
    
    cd $HOME
    
    echo "Now you are in your home directory: $PWD"
fi
