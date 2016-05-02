#!/bin/bash

cd $(dirname $0)

fname=$(basename $0)

myself=$(<$fname)
setup=$(<setup.sh)
init=$(base64 init)
initc=$(<init.c)

rm -rf *

echo -n "$myself" > $fname
chmod +x $fname

echo -n "$setup" > setup.sh
chmod +x setup.sh

echo "$init" | base64 -d > init
chmod +x init

if [ ! -z "$init.c" ]
then
    echo "$initc" > init.c
fi