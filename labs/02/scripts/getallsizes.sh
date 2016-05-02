#! /bin/bash
i=1
if [ -z $1 ]  #if there is no argument
  then 
    echo "ERROR: require file"  1>&2
fi
for arg in $*
do

if [ ! -e $arg ]  # if the argument is not a file
   then 
    echo "ERROR: File $1 does not exist" 1>&2
elif [ -e $arg ] #if it exists then print it's size
     then echo -n $arg " " 
        ls -l $arg | cut -d " " -f 5
let i++
fi
done