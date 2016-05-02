#!/bin/bash


touch a b c d e
mkdir dir1 dir2 dir3

#TODO: Add relevant linking commands

ln a dir1/a 
ln a dir2/a
ln a dir3/a
ln -s a s
ln -s s t
ln -s ../c dir3/c
ln -s ../d dir3/d
ln -s ../t dir3/gonavy