#!/bin/bash

grep "$1" /etc/passwd | cut -d ":" -f 5 