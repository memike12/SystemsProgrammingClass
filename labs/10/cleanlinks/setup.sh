#!/bin/bash

#TODO: Add relevent link clean up commands
rm b c d k dir1/f dir2/g dir3/j

ln -s a b
ln -s a c
ln -s a d
ln -s e k
ln -s  ../a dir1/f
ln -s ../a dir2/g

ln -s i dir3/j