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


function compile_term-status(){
    if [ "$(basename $PWD)"  == "term-status" ]
    then
	clang -g -Wall    foursons.c   -o foursons
    else
	cd term-status
	clang -g -Wall    foursons.c   -o foursons
	cd ..
    fi
}

function clean_term-status(){
    if [ "$basename $PWD)"  == "term-status" ]
    then
	rm -f foursons
    else
	cd term-status
	rm -f foursons
	cd ..
    fi
}

function compile_timer(){
    if [ "$(basename $PWD)"  == "timer" ]
    then
	clang -g -Wall    timer.c   -o timer
    else
	cd timer
	clang -g -Wall    timer.c   -o timer
	cd ..
    fi
}

function clean_timer(){
    if [ "$basename $PWD)"  == "timer" ]
    then
	rm -f timer
    else
	cd timer
	rm -f timer
	cd ..
    fi
}

function compile_mini-sh(){
    if [ "$(basename $PWD)"  == "mini-sh" ]
    then
	clang -g -Wall -lreadline    mini-sh.c   -o mini-sh
    else
	cd mini-sh
	clang -g -Wall -lreadline   mini-sh.c   -o mini-sh
	cd ..
    fi
}

function clean_mini-sh(){
    if [ "$basename $PWD)"  == "mini-sh" ]
    then
	rm -f mini-sh
    else
	cd mini-sh
	rm -f mini-sh
	cd ..
    fi
}


function compile(){
    compile_term-status
    compile_timer
    compile_mini-sh
}

function clean(){
   clean_term-status
   clean_timer
   clean_mini-sh
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


function test_makefile(){
    echo "--- TEST MAKEFILE ---"

    clean_term-status
    cd term-status
    make 1>/dev/null 2>&1
    res=$(ls foursons)
    utest_nz "$res" "term-status (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls foursons 2>/dev/null)
    utest_z "$res" "term-status (make clean)"
    cd ..

    clean_timer
    cd timer
    make 1>/dev/null 2>&1
    res=$(ls timer)
    utest_nz "$res" "timer (make)"

    make clean 1>/dev/null 2>&1
    res=$(ls timer 2>/dev/null)
    utest_z "$res" "timer (make clean)"
    cd ..

    clean_mini-sh
    cd mini-sh
    make 1>/dev/null 2>&1
    res=$(ls mini-sh)
    utest_nz "$res" "mini-sh (make)"


    make clean 1>/dev/null 2>&1
    res=$(ls mini-sh 2>/dev/null)
    utest_z "$res" "mini-sh (make clean)"
    cd ..

}

function test_term-status(){
    echo "--- TEST TERM-STATUS ---"
    
    cmd="./term-status/foursons | grep -o \"terminated and exited with status 0\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (term status 0)"

    cmd="./term-status/foursons | grep -o \"terminated and exited due to signal Aborted and also core dumped\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (signal Abort/core dumped)"

    cmd="./term-status/foursons | grep -o \"terminated and exited due to signal Segmentation fault and also core dumped\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (signal segfault/core dumped)"

    cmd="./term-status/foursons | grep -o \"terminated and exited with status 16\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (signal segfault/core dumped)"

    cmd="./term-status/foursons"
    res=(ecal $cmd)
    cpids=$(echo $res | head -4 | cut -d ":" -f 4 | sort)
    expect=$(echo $res | tail -4 | cut -d ":" -f 4 | sort)
    utest "$cpids" "$expect" "$cmd (all pid's printed) ($cpids =?= $expect)"
    
    echo
}

function test_timer(){
    echo "--- TEST TIMER ---"
    
    cmd="./timer/timer 2>&1"
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (prints eror with no arguments)"

    cmd="./timer/timer BAD 2>&1"
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (prints eror for bad command)"

    cmd="./timer/timer /bin/ls | head -1"
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (execute command with full path)"

    cmd="./timer/timer ls | head -1"
    res=$(eval $cmd)
    utest_nz "$res" "$cmd (execute basic command with searching path)"

    cmd="./timer/timer ls /proc/cpuinfo | head -1"
    res=$(eval $cmd)
    expect="/proc/cpuinfo"
    utest "$res" "$expect" "$cmd (execute command with arugment)" 

    cmd="./timer/timer sleep 2 | grep -o \"[0-9]*\\\\.[0-9]*\" | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="2"
    utest "$res" "$expect" "$cmd (times properly, 2 seconds)" 

    cmd="./timer/timer sleep 1 | grep -o \"[0-9]*\\\\.[0-9]*\" | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "$cmd (times properly, 1 second)" 

    cmd="./timer/timer cat /proc/cpuinfo /proc/meminfo /proc/stat | tail -1 | grep -o \"[0-9]*\\\\.[0-9]*\" | cut -d \".\" -f 2"
    res=$(eval $cmd)
    expect="0000"
    utest_ne "$res" "$expect" "$cmd (times properly, milisecond)" 

    echo
}

function test_mini-sh(){
    echo "--- TEST MINI-SH ---"

    
    cmd="echo \"ls\" | ./mini-sh/mini-sh | sed \"s/mini-sh ([0-9.]*) #> .*//g\" | sed \"/^$/d\""
    res=$(eval $cmd)

    utest_nz "$res" "$cmd (execute ls)"

    cmd="echo \"BAD\" | ./mini-sh/mini-sh 2>&1| sed \"s/mini-sh ([0-9.]*) #> .*//g\" | sed \"/^$/d\""
    res=$(eval $cmd)

    utest_nz "$res" "$cmd (prints errro on bad command)"

    expect=$(echo $res | grep "mini-sh")
    utest_nz "expect" "$cmd (execute ls, finds 'mini-sh')"

    cmd="echo \"ls /proc/cpuinfo\" | ./mini-sh/mini-sh | sed \"s/mini-sh ([0-9.]*) #> .*//g\" | sed \"/^$/d\""
    res=$(eval $cmd)
    expect="/proc/cpuinfo"
    utest "$res" "$expect" "$cmd (execute ls with one argument)"

    cmd="echo \"ls /proc/cpuinfo /proc/meminfo /proc/stat\" | ./mini-sh/mini-sh | sed \"s/mini-sh ([0-9.]*) #> .*//g\" | sed \"/^$/d\" | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="/proc/cpuinfo /proc/meminfo /proc/stat "
    utest "$res" "$expect" "$cmd (execute ls with multiple arguments)"

    cmd="echo -e \"sleep 2\" | ./mini-sh/mini-sh | tail -1 | grep -o \"[0-9.]*\" | cut -d \".\" -f 1"
    res=$(eval $cmd)
    expect="2"
    utest "$res" "$expect" "$cmd (times, 2 seconds)"

    cmd="echo -e \"sleep 2\\\\nsleep 3\" | ./mini-sh/mini-sh | tail -2 | grep -o \"mini-sh ([0-9.]*)\" | grep -o \"[0-9.]*\" | cut -d \".\" -f 1 | tr \"\\\\n\" \" \"" 
    res=$(eval $cmd)
    expect="2 3 "
    utest "$res" "$expect" "$cmd (times, 2 seconds and 3 seconds)"

}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

clean
compile

echo

#****************************
# Comment out tests you aren't working on
#***************************
test_term-status
test_timer
test_mini-sh
test_makefile