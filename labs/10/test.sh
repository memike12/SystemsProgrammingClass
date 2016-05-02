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


function test_makelinks(){
    echo "--- TEST MAKELINKS ---"

    cd makelinks
    ./clean.sh
    ./setup.sh

    cmd="ls -li | grep \"[0-9] [abcde]$\" | cut -d \" \" -f 1 | sort | uniq | wc -l"
    res=$(eval $cmd)
    expect="5"
    utest "$res" "$expect" "(a,b,c,d,e are different i-nodes) $cmd ($res)"


    cmd="ls -li | grep \"s -> a$\""
    res=$(eval $cmd)
    utest_nz "$res" "(s->a) $cmd "

    cmd="ls -li | grep \"t -> s$\""
    res=$(eval $cmd)
    utest_nz "$res" "(t->s) $cmd "

    cmd="ls -li a dir1/a | cut -d \" \" -f 1 | sort | uniq | wc -l"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(a dir1/a linked) $cmd ($res)"

    cmd="ls -li a dir2/a | cut -d \" \" -f 1 | sort | uniq | wc -l"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(a dir2/a linked) $cmd ($res)"


    cmd="ls -li a dir3/a | cut -d \" \" -f 1 | sort | uniq | wc -l"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(a dir3/a linked) $cmd ($res)"

    cmd="ls -li dir3/c | grep \"c -> \\\\.\\\\./c$\""
    res=$(eval $cmd)
    utest_nz "$res" "(dir3/c -> \\\\.\\\\./c) $cmd"

    cmd="ls -li dir3/d | grep \"d -> \\\\.\\\\./d$\""
    res=$(eval $cmd)
    utest_nz "$res"  "(dir3/d -> \\\\.\\\\./d) $cmd"

    cmd="echo \"Go Navy\" >> a ; cat dir3/gonavy"
    res=$(eval $cmd)
    expect="Go Navy"
    utest "$res" "$expect" "(follow go Navy) $cmd ($res)"
    

    cd ..
    echo
}

function test_cleanlinks(){
    echo "--- TEST CLEANLINKS ---"

    cd cleanlinks
    ./clean.sh
    ./init
    ./setup.sh


    cmd="ls -l | grep \" -> a$\" | cut -d \" \" -f 12 | tr \"\\\\n\" \" \"" 
    res=$(eval $cmd)
    expect="b c d "
    utest "$res" "$expect" "(sym links to a) $cmd"

    cmd="ls -l | grep \"k -> e$\" "
    res=$(eval $cmd)
    utest_nz "$res" "(k -> e) $cmd"

    cmd="ls -l dir1/f | grep \"f -> \\\\.\\\\./a$\" "
    res=$(eval $cmd)
    utest_nz "$res" "(dir1/f -> ../a) $cmd"

    cmd="ls -l dir2/g | grep \"g -> \\\\.\\\\./a$\" "
    res=$(eval $cmd)
    utest_nz "$res" "(dir2/g -> ../a) $cmd"

    cmd="ls -l dir3/j | grep \"j -> i$\" "
    res=$(eval $cmd)
    utest_nz "$res" "(j -> i) $cmd"

    cmd="ls -li * | grep \"^[0-9]\" | cut -d \" \" -f 1 | sort | uniq | wc -l"
    res=$(eval $cmd)
    expect=15
    utest "$res" "$expect" "(right number of i-nodes) $cmd"

    cd ..
    echo
}

function test_llines(){
    echo "--- TEST CLEANLINKS ---"

    cd llines

    make

    cmd="grep fopen llines.c"
    res=$(eval $cmd)
    utest_z "$res" "(no fopen()) $cmd"

    cmd="grep fseek llines.c"
    res=$(eval $cmd)
    utest_z "$res" "(no fseek()) $cmd"

    cmd="grep ftell llines.c"
    res=$(eval $cmd)
    utest_z "$res" "(no ftell()) $cmd"

    cmd="grep lseek llines.c"
    res=$(eval $cmd)
    utest_nz "$res" "(yes lseek()) $cmd"
    
    cmd="./llines GoNavy.txt"
    res=$(eval $cmd)
    expect="Beat Army!"
    utest "$res" "$expect" "(no args) $cmd"


    cmd="./llines -s 3 GoNavy.txt"
    res=$(eval $cmd)
    expect="t Army!"
    utest "$res" "$expect" "(just -s) $cmd"

    cmd="./llines -s 10 GoNavy.txt"
    res=$(eval $cmd)
    expect=""
    utest "$res" "$expect" "(-s 10s) $cmd"


    cmd="./llines -s 3 -e 5 GoNavy.txt"
    res=$(eval $cmd)
    expect="t "
    utest "$res" "$expect" "(-s and -e) $cmd"

    cmd="./llines -e 5 GoNavy.txt"
    res=$(eval $cmd)
    expect="rmy!"
    utest "$res" "$expect" "(just -e) $cmd"

    cmd="./llines -s 7 -e 5 GoNavy.txt 2>&1"
    res=$(eval $cmd)
    utest_nz "$res" "(error on bad args) $cmd"

    cmd="./llines -s 1845 -e 1850 dickens.txt | tr \"\\\\n\" \" \" | tr -s \" \""
    res=$(eval $cmd)
    expect="CHAPT"
    utest "$res" "$expect" "(dickens) $cmd ($res =?= $expect)"

    cd ..
}

function test_flines(){
    echo "--- TEST CLEANLINKS ---"

    cd flines

    make 1>/dev/null 2>/dev/null

    cmd="grep \"[^f]open\" flines.c"
    res=$(eval $cmd)
    utest_z "$res" "(no open()) $cmd"

    cmd="grep lseek flines.c"
    res=$(eval $cmd)
    utest_z "$res" "(no lseek()) $cmd"

    cmd="grep fseek flines.c"
    res=$(eval $cmd)
    utest_nz "$res" "(yes fseek()) $cmd"
    
    cmd="./flines GoNavy.txt"
    res=$(eval $cmd)
    expect="Beat Army!"
    utest "$res" "$expect" "(no args) $cmd"


    cmd="./flines -s 3 GoNavy.txt"
    res=$(eval $cmd)
    expect="t Army!"
    utest "$res" "$expect" "(just -s) $cmd"

    cmd="./flines -s 10 GoNavy.txt"
    res=$(eval $cmd)
    expect=""
    utest "$res" "$expect" "(-s 10s) $cmd"


    cmd="./flines -s 3 -e 5 GoNavy.txt"
    res=$(eval $cmd)
    expect="t "
    utest "$res" "$expect" "(-s and -e) $cmd"

    cmd="./flines -e 5 GoNavy.txt"
    res=$(eval $cmd)
    expect="rmy!"
    utest "$res" "$expect" "(just -e) $cmd"

    cmd="./flines -s 7 -e 5 GoNavy.txt 2>&1"
    res=$(eval $cmd)
    utest_nz "$res" "(error on bad args) $cmd"
    
    cmd="./flines -s 1845 -e 1850 dickens.txt | tr \"\\\\n\" \" \" | tr -s \" \""
    res=$(eval $cmd)
    expect="CHAPT"
    utest "$res" "$expect" "(dickens) $cmd ($res =?= $expect)"

    echo
    cd ..
}

if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

test_makelinks
test_cleanlinks
test_llines
test_flines