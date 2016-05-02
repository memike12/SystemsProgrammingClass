#!/bin/bash

i=1
for arg in $@
do
    echo "arg$i: $arg"
    let i++
done