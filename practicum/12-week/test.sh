#!/bin/bash

red="\e[0;31m"
green="\e[0;32m"
nc="\e[0m"     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}

function ctime(){
    date +"%a %b %d %H:%M:%S %Y"
}




function utest( ){

    if [ "$1" == "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $3"
}

function utest_ne( ){

    if [ "$1" != "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $3"
}

function utest_nz( ){
    if [ ! -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $2"
}

function utest_z( ){
    if [ -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $2"
}


function test_prob1(){
    echo "--- TEST PROB 1 ---"
    
    cd prob1
    
    cmd="cat Makefile | grep \"rpn:\""
    res=$(eval $cmd)
    utest_nz "$res" "(rpn target) $cmd"

    cmd="cat Makefile | grep \"rpn\\\\.o:\""
    res=$(eval $cmd)
    utest_nz "$res" "(rpn.o target) $cmd"

    cmd="cat Makefile | grep \"mathlib\\\\.o:\""
    res=$(eval $cmd)
    utest_nz "$res" "(mathlib.o target) $cmd"

    cmd="cat Makefile | grep \"clean:\""
    res=$(eval $cmd)
    utest_nz "$res" "(clean target) $cmd"

    cmd="cat Makefile | grep \"^CC\""
    res=$(eval $cmd)
    utest_z "$res" "(no CC) $cmd ($res)"

    cmd="cat Makefile | grep \"^CFLAGS\""
    res=$(eval $cmd)
    utest_z "$res" "(no CFLAGS) $cmd"

    cmd="rm -f mathlib.o; make mathlib.o | grep \"clang\" | grep \"\-c\""
    res=$(eval $cmd)
    utest_nz "$res" "(compiled mathlib.o) $cmd"
    
    cmd="test -e mathlib.o ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "(mathlib.o created) $cmd ($res)"


    cmd="rm -f rpn.o; make rpn.o | grep \"clang\" | grep \"\-c\""
    res=$(eval $cmd)
    utest_nz "$res" "(compiled rpn.o) $cmd"
    
    cmd="test -e rpn.o ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "(rpn.o created) $cmd"
    
    cmd="make; test -e rpn; echo \$?"
    res=$(eval $cmd | tail -c 2)
    expect="0"
    utest "$res" "$expect" "(compiles rpn) $cmd"
    
    cmd="echo \"1 1 +\" | ./rpn | grep \"^0:\""
    res=$(eval $cmd)
    expect="0: 2"
    utest "$res" "$expect" "(rpn functions: 1 1 +) $cmd"

    cmd="echo \"1 2 *\" | ./rpn | grep \"^0:\""
    res=$(eval $cmd)
    expect="0: 2"
    utest "$res" "$expect" "(rpn functions: 1 2 *) $cmd"

    cmd="echo \"3 !\" | ./rpn | grep \"^0:\""
    res=$(eval $cmd)
    expect="0: 6"
    utest "$res" "$expect" "(rpn functions: 3 !) $cmd"

    cmd="echo \"4 5 -\" | ./rpn | grep \"^0:\""
    res=$(eval $cmd)
    expect="0: -1"
    utest "$res" "$expect" "(rpn functions: 4 5 -) $cmd"

    cmd="make clean; test -e rpn; echo -n \$?; test -e rpn.o; echo -n \$?; test -e mathlib.o; echo -n \$?"
    res=$(eval $cmd | tail -c 3)
    expect="111"
    utest "$res" "$expect" "(make clean) $cmd"
    
    cd ..
    echo
}

function test_prob2(){
    echo "--- TEST PROB 2 ---"
    
    cd prob2

    make clean > /dev/null 2>/dev/null
    make > /dev/null 2>/dev/null
    
    sleep 1 && killall grandchildren 2>/dev/null &
    cmd="timeout 1 ./grandchildren < GoNavy.txt"
    res=$(eval $cmd)
    expect="Beat Army!"
    utest "$res" "$expect" "(Pipes GoNavy.txt) $cmd ($res)"

    sleep 1 && killall grandchildren 2>/dev/null &
    cmd="timeout 1 ./grandchildren < GoNavy.txt; echo -ne \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="Beat Army! 0"
    utest "$res" "$expect" "(widows properly) $cmd ($res)"

    sleep 1 && killall grandchildren 2>/dev/null &
    cmd="timeout 1 ./grandchildren < BeatArmy.txt"
    res=$(eval $cmd)
    expect="Go Navy!"
    utest "$res" "$expect" "(Pipes BeatArmy.txt) $cmd ($res)"

    sleep 1 && killall grandchildren 2>/dev/null &
    cmd="timeout 1 ./grandchildren < BeatArmy.txt; echo -ne \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="Go Navy! 0"
    utest "$res" "$expect" "(widows properly) $cmd ($res)"

    sleep 1 && killall grandchildren 2>/dev/null &
    cmd="cat GoNavy.txt | timeout 1 ./grandchildren"
    res=$(eval $cmd)
    expect="Beat Army!"
    utest "$res" "$expect" "(cats GoNavy.txt) $cmd ($res)"

    sleep 1 && killall grandchildren 2>/dev/null &
    cmd="cat GoNavy.txt | timeout 1 ./grandchildren; echo -ne \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="Beat Army! 0"
    utest "$res" "$expect" "(widows properly) $cmd ($res)"

    cd ..
    echo
}

function test_prob3(){
    echo "--- TEST PROB 3 ---"
    
    cd prob3

    make clean 2>/dev/null >/dev/null
    make 2>/dev/null >/dev/null

    sigorig="signal(signum, handler);"


    sleep 1 && killall ping 2>/dev/null &
    cat ping.c | sed "s/$sigorig/signum=31;$sigorig;/" | clang -xc - -o ping
    cmd="timeout 1 ./pong; echo \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="ping 31 pong 31 ACK 31 0 "
    utest "$res" "$expect" "(signal 31) $cmd ($res)"

    sleep 1 && killall ping 2>/dev/null &
    cat ping.c | sed "s/$sigorig/signum=6;$sigorig;/" | clang -xc - -o ping
    cmd="./pong"
    res=$(eval $cmd | tr "\n" " ")
    expect="ping 6 pong 6 ACK 6 "
    utest "$res" "$expect" "(signal 6) $cmd ($res)"

    sleep 1 && killall ping 2>/dev/null &
    cat ping.c | sed "s/$sigorig/signum=13;$sigorig;/" | clang -xc - -o ping
    cmd="timeout 1 ./pong; echo \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="ping 13 pong 13 ACK 13 0 "
    utest "$res" "$expect" "(signal 31) $cmd ($res)"

    make clean >/dev/null 2>/dev/null
    make >/dev/null 2>/dev/null

    sleep 1 && killall ping 2>/dev/null &
    cmd="timeout 1 ./pong | cut -d \" \" -f 2 | sort | python -c \"import sys; from itertools import groupby; from operator import itemgetter; lines=[l.strip() for l in sys.stdin]; sys.stdout.write('1') if len(lines)==3 and len(map(itemgetter(0), groupby(lines))) == 1 else sys.stdout.write('0')\""
    res=$(eval $cmd | tr "\n" " ")
    expect="1"
    utest "$res" "$expect" "(random 1) $cmd ($res)"

    sleep 1 && killall ping 2>/dev/null &
    cmd="timeout 1 ./pong | cut -d \" \" -f 2 | sort | python -c \"import sys; from itertools import groupby; from operator import itemgetter; lines=[l.strip() for l in sys.stdin]; sys.stdout.write('1') if len(lines)==3 and len(map(itemgetter(0), groupby(lines))) == 1 else sys.stdout.write('0')\""
    #cmd="timeout 1 ./pong | cut -d \" \" -f 2 | sort | uniq | wc -l"
    res=$(eval $cmd | tr "\n" " ")
    expect="1"
    utest "$res" "$expect" "(random 2) $cmd ($res)"

    cd ..
    echo
    
}
if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

test_prob1
test_prob2
test_prob3

