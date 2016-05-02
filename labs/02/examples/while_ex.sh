#!/bin/bash

i=1
while [ $i -le 10 ]
do
    echo $i
    let i++ # you can use incrementers in lets
            # and, you don't need to use the $ here
done
    