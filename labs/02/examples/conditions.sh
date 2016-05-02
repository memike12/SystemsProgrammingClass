#!/bin/bash

#string
var=adam
if [ $1 = $var ] ; then echo "string $1 equals $var" ; fi
if [ $1 == $var ] ; then echo "string $1 equals $var" ; fi
if [ $1 != $var ] ; then echo "string $1 does not equals $var" ; fi
if [ -z $1 ] ; then echo "string $1 is empty!"; fi
if [ -n $1 ] ; then echo "string $1 is not empty!"; fi

#numeric
a=1
if [ $a -eq $1 ] ; then echo "number $1 equals $a" ; fi
if [ $a -ne $1 ] ; then echo "number $1 does not equal $a" ; fi
if [ $a -gt $1 ] ; then echo "$a is greater than $1" ; fi
if [ $a -lt $1 ] ; then echo "$a is less than $1" ; fi

#file/dir properties
if [ -d $1 ] ; then echo "$1 exists and is a directory!" ; fi
if [ -e $1 ] ; then echo "$1 exists!" ; fi
if [ -f $1 ] ; then echo "$1 exists and is not a directory!" ; fi
if [ -r $1 ] ; then echo "$1 exists and is readable!" ; fi
if [ -s $1 ] ; then echo "$1 exists and has size greater than zero!" ; fi
if [ -w $1 ] ; then echo "$1 exists and is writable!" ; fi
if [ -x $1 ] ; then echo "$1 exists and is executable!" ; fi

# NOTE: Since everything's on the same line, I need ;s between
# the if and the then and between the then and the fi.