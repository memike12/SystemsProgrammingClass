#! /bin/bash

    if [ -z $2 ]  #if there is no argument
      then 
    echo "ERROR: Require path and size" 
    exit 2

    fi    
    
    for arg in $*
    do 
        if [[ $arg != *[!0-9]* ]]
        then
        echo -n ""
        else
        response=$(./isbiggerthan.sh $1 $arg)
        if [ "$?" = "0" ]
        then
            echo "$arg"
        fi
fi
done
