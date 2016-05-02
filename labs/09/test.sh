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


function compile_shredder(){
    if [ "$(basename $PWD)"  == "shredder" ]
    then
	make 1>/dev/null 2>/dev/null
    else
	cd shredder
	make >/dev/null 2>/dev/null
	cd ..
    fi
}

function compile_sigaction(){
    if [ "$(basename $PWD)"  == "sigaction" ]
    then
	make 0 1>/dev/null 2>/dev/null
    else
	cd sigaction
	make 0 1>/dev/null 2>/dev/null
	cd ..
    fi
}


function clean_unroll(){
    if [ "$basename $PWD)"  == "shredder" ]
    then
	make clean
    else
	cd shredder
	make clean >/dev/null 2>/dev/null
	cd ..
    fi
}

function clean_pipe-dup(){
    if [ "$basename $PWD)"  == "sigaction" ]
    then
	make clean
    else
	cd sigaction
	make clean >/dev/null 2>/dev/null
	cd ..
    fi
}


function compile(){
    compile_shredder
    compile_sigaction
}

function clean(){
    clean_shredder
    clean_sigaction
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


function test_shredder(){
    echo "--- TEST SHREDDER ---"

    touch test.fs
    cmd="./shredder/shredder ls | grep test.fs"
    res=$(eval $cmd)
    utest_nz "$res" "(exec's command) $cmd"
    rm test.fs

    cmd="./shredder/shredder ls | grep \"Blast that grotesque ganglion\! You let them get away\!\""
    res=$(eval $cmd)
    utest_nz "$res" "(prints message \"Blast ...\") $cmd"
    
    cmd="./shredder/shredder sleep 1 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock Blast that grotesque ganglion! You let them get away! "
    utest "$res" "$expect" "(prints message and tick's once) $cmd"
    
    cmd="./shredder/shredder sleep 2 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock Blast that grotesque ganglion! You let them get away! "
    utest "$res" "$expect" "(prints message and tick's twice) $cmd"

    cmd="./shredder/shredder sleep 3 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock Sayonara you shell-backed simpletons. I'll get you next time! "
    utest "$res" "$expect" "(prints \"Sayonara...\" and tick's three) $cmd"

    cmd="./shredder/shredder sleep 5 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock 4: tick-tock 5: tick-tock Tonight I dine on turtle soup! Muhaha! "
    utest "$res" "$expect" "(prints \"Tonight ...\" and tick's five times) $cmd"


    cmd="./shredder/shredder cat | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock 4: tick-tock 5: tick-tock Tonight I dine on turtle soup! Muhaha! "
    utest "$res" "$expect" "(prints \"Tonight ...\" and tick's five times) $cmd"

    cmd="./shredder/shredder cat | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock 4: tick-tock 5: tick-tock Tonight I dine on turtle soup! Muhaha! "
    utest "$res" "$expect" "(prints \"Tonight ...\" and tick's five times) $cmd"

    echo
}

function test_sigaction(){
    echo "--- TEST SIGACTION ---"

    cmd="./sigaction/moresons | grep \"Parent: Child 0: [0-9]* terminated and exited with status 16\""
    res=$(eval $cmd)
    utest_nz "$res" "(terminates message no. 16) $cmd"

    cmd="./sigaction/moresons | grep \"Parent: Child 1: [0-9]* terminated and exited due to signal no. 11\""
    res=$(eval $cmd)
    utest_nz "$res" "(terminates message no. 11) $cmd"


    cmd="./sigaction/moresons | grep \"Parent: Child 2: [0-9]* terminated and exited due to signal no. 14\""
    res=$(eval $cmd)
    utest_nz "$res" "(terminates message no. 14) $cmd"

    cmd="./sigaction/moresons | grep \"Parent: Child 3: [0-9]* terminated and exited with status 0\""
    res=$(eval $cmd)
    utest_nz "$res" "(exit with status) $cmd"
    
    cmd="./sigaction/moresons | grep \"Parent: Child 0: [0-9]* stopped, continuing ...\""
    res=$(eval $cmd)
    utest_nz "$res" "(caught stopped process) $cmd"


    cmd="./sigaction/moresons | grep \"Parent: Child 0: [0-9]* just continued\""
    res=$(eval $cmd)
    utest_nz "$res" "(caught continued process) $cmd"
   
    cmd="./sigaction/moresons"
    res=$(eval $cmd)
    cpids=$(echo "$res" | grep "^Child" | cut -d ":" -f 2 | cut -d " " -f 2 | sort | uniq | tr "\n" " ")
    expect=$(echo "$res"| grep "^Parent" | cut -d ":" -f 3 | cut -d " " -f 2 | sort | uniq | tr "\n" " ")
    utest "$cpids" "$expect" "$cmd (all pid's printed) (\"$cpids\" =?= \"$expect\")"

    cmd="./sigaction/moresons"
    res=$(eval $cmd)
    cpids=$(echo "$res" | grep "^Child" | cut -d ":" -f 1,2 | sort | uniq | tr "\n" " ")
    expect=$(echo "$res"| grep "^Parent" | cut -d ":" -f 2,3 | cut -d " " -f 2,3,4 | sort | uniq | tr "\n" " ")
    utest "$cpids" "$expect" "$cmd (all pid's printed) (\"$cpids\" =?= \"$expect\")"
 
    echo
}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

compile

test_shredder
test_sigaction


