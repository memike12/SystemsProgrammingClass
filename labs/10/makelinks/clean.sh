#!/bin/bash

cd $(dirname $0)

fname=$(basename $0)

myself=$(< $fname)
setup=$(< setup.sh)

rm -rf *

echo -n "$myself" > $fname
chmod +x $fname

echo -n "$setup" > setup.sh
chmod +x setup.sh