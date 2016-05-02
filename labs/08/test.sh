#!/bin/bash

red='\e[0;31m'
green='\e[0;32m'
nc='\e[0m'     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}

function ctime(){
    date +"%a %b %d %H:%M:%S %Y"
}


function compile_unroll(){
    if [ "$(basename $PWD)"  == "unroll" ]
    then
	make 1>/dev/null 2>/dev/null
    else
	cd unrolll
	make >/dev/null 2>/dev/null
	cd ..
    fi
}

function compile_pipe-dup(){
    if [ "$(basename $PWD)"  == "pipe-dup" ]
    then
	make 0 1>/dev/null 2>/dev/null
    else
	cd pipe-dup
	make 0 1>/dev/null 2>/dev/null
	cd ..
    fi
}


function clean_unroll(){
    if [ "$basename $PWD)"  == "unroll" ]
    then
	make clean
    else
	cd unroll
	make clean >/dev/null 2>/dev/null
	cd ..
    fi
}

function clean_pipe-dup(){
    if [ "$basename $PWD)"  == "pipe-dup" ]
    then
	make clean
    else
	cd pipe-dup
	make clean >/dev/null 2>/dev/null
	cd ..
    fi
}


function compile(){
    compile_unroll
    compile_pipe-dup
}

function clean(){
    clean_unroll
    clean_pipe-dup
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


function test_unroll(){
    echo "--- TEST UNROLL ---"

    cd unroll    
    compile_unroll

    cmd="{ time ./sleep-unroll \"sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(\"sleep 1\" runs for 1 second) $cmd"

    cmd="{ time ./sleep-unroll \"sleep 1 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(\"sleep 1 | sleep 1\" runs for 1 second) $cmd"

    cmd="{ time ./sleep-unroll \"sleep 1 | sleep 1 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(\"sleep 1 | sleep 1 | sleep 1\" runs for 1 second) $cmd"


    cmd="{ time ./sleep-unroll \"sleep 1 | sleep 2 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="2"
    utest "$res" "$expect" "(\"sleep 1 | sleep 2 | sleep 1\" runs for 2 second) $cmd"


    cmd="{ time ./sleep-unroll \"sleep 0 | sleep 2 | sleep 1\" ; } 2>&1 | grep real | cut -d \"m\" -f 2 | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="2"
    utest "$res" "$expect" "(\"sleep 0 | sleep 2 | sleep 1\" runs for 2 second) $cmd"

    cmd="{ ./sleep-unroll \"sleep 2\" & }; pid=\$!; sleep 1; [ \"\$(ps --ppid \$pid -o pid | tail -1)\" == \"\$(ps --ppid \$pid -o pgid | tail -1)\" ] ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "(child in own group) $cmd"

    cmd="{ ./sleep-unroll \"sleep 2 | sleep 2 | sleep 2 | sleep 2\" & }; pid=\$!; sleep 1; [ \"\$(ps --ppid \$pid -o pid | tail -4 | head -1)\" == \"\$(ps --ppid \$pid -o pgid | tail -4 | uniq)\" ] ; echo \$?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "(all children in same group, with 1st child as leader) $cmd"

    cmd="./sleep-unroll \"head -c 20 /dev/zero\" | wc -c "
    res=$(eval $cmd)
    expect="20"
    utest "$res" "$expect" "(executes normal commands) $cmd"


    cd ..
    echo
}

function test_pipe-dup(){
    echo "--- TEST PIPE-DUP ---"
    
    cd pipe-dup

    make 0 2>/dev/null >/dev/null

    cmd="./babypipe"
    res=$(eval $cmd)
    expect=$(cat /etc/passwd | cut -d : -f 7 | sort | uniq)
    utest "$res" "$expect" "(make 0) $cmd"

    make 1 2>/dev/null >/dev/null
    cmd="./babypipe"
    res=$(eval $cmd)
    expect=$(cat sample-db.csv | cut -d , -f 8 | sort | uniq | wc -l)
    utest "$res" "$expect" "(make 1) $cmd"

    make 2 2>/dev/null >/dev/null
    cmd="./babypipe"
    res=$(eval $cmd)
    expect=$(cat sample-db.csv | cut -d , -f 10 | cut -d - -f 1 | sort | uniq | wc -l)
    utest "$res" "$expect" "(make 2) $cmd"

    make 3 2>/dev/null >/dev/null
    cmd="cat sample-db.csv | ./babypipe"
    res=$(eval $cmd)
    expect=$(cat sample-db.csv | cat | cut -d , -f 10 | cut -d - -f 1 | sort | uniq | wc -l)
    utest "$res" "$expect" "(make 3) $cmd"

    make 0 2>/dev/null >/dev/null
    cd ..
    echo
}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

clean

test_unroll
test_pipe-dup


