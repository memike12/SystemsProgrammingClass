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

function ucount(){

    python -c "
import sys
d={}
for l in sys.stdin:
   d.setdefault(l.strip(),0) 
   d[l.strip()]+=1
for k in d: 
   print d[k],k
"

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


function test_myhost(){
    echo "--- TEST MYHOST ---"

    cd myhost
    make clean >/dev/null 2>/dev/null
    make >/dev/null 2>/dev/null

    cmd="./myhost www.usna.edu"
    res=$(eval $cmd)
    expect="www.usna.edu has address 10.4.32.41"
    utest "$res" "$expect" "(www.usna.edu) $cmd"

    cmd="./myhost google.com | grep \"has address\" | sort | uniq | wc -l | tr -s \" \""
    res=$(eval $cmd)
    expect="11"
    utest "$res" "$expect" "(find 11 address for google.com) $cmd ($res)"

    cmd="./myhost google.com | grep \"has address\" | ucount | cut -d \" \" -f 1 | sort | uniq | wc -l | tr -s \" \""
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(address don't repeate for google.com) $cmd ($res)"

    cmd="./myhost google.com | grep \"has address\" | sort | uniq | wc -l | tr -s \" \""
    res=$(eval $cmd)
    expect="11"
    utest "$res" "$expect" "(find 11 address for google.com) $cmd ($res)"

    cmd="./myhost google.com | grep \"has address\" | ucount | cut -d \" \" -f 1 | sort | uniq | wc -l | tr -s \" \""
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(address don't repeate for google.com) $cmd ($res)"

    echo "=== EXTRA CREDIT ==="
    cmd="./myhost www.cis.upenn.edu | sort | tr \"\\\\n\" \" \" "
    res=$(eval $cmd)
    expect="www.cis.upenn.edu has address 158.130.69.163 www.cis.upenn.edu has IPv6 address 2607:f470:8:64:5ea5::d "
    utest "$res" "$expect" "(ipv6 address for www.cis.upenn.edu) $cmd ($res)"

    cd ..
    echo
}

function test_mywget(){
    echo "--- TEST MYHOST ---"

    cd mywget
    make clean >/dev/null 2>/dev/null
    make >/dev/null 2>/dev/null

    cal=$(echo -e "GET /Users/cs/aviv/classes/ic221/s14/cal.html HTTP/1.0\n\r" | netcat www.usna.edu 80)

    rm -f cal.html
    cmd="./mywget www.usna.edu /Users/cs/aviv/classes/ic221/s14/cal.html >/dev/null 2>/dev/null; cat cal.html"
    res=$(eval $cmd)
    expect="$cal"
    utest "$res" "$expect" "(download course calendar on port 80) $cmd"
    rm -f cal.html

    cmd="./mywget www.usna.edu /Users/cs/aviv/classes/ic221/s14/cal.html 2>&1"
    res=$(eval $cmd)
    expect="HTTP/1.1 200 OK"
    utest "$res" "$expect" "(Outputs OK code 200) $cmd"
    rm -f cal.html

    saturn=$(echo -e "GET /Users/cs/aviv/saturn.txt HTTP/1.0\n\r" | netcat www.usna.edu 80)

    rm -f saturn.txt
    cmd="./mywget www.usna.edu /Users/cs/aviv/saturn.txt  >/dev/null 2>/dev/null; cat saturn.txt"
    res=$(eval $cmd)
    expect="$saturn"
    utest "$res" "$expect" "(download file saturn.txt on port 80) $cmd"
    rm -f saturn.txt

    cmd="./mywget badbabdabda /index.html 2>&1 | grep ERROR"
    res=$(eval $cmd)
    utest_nz "$res" "(ERROR on bad domain) $cmd"

    rm -f doesnotexist.html
    cmd="./mywget www.usna.edu /doesnotexist.html 2>&1"
    expect="HTTP/1.1 404 Not Found"
    res=$(eval $cmd)
    utest "$res" "$expect" "(ERROR on does not exist 404) $cmd"

    cmd="ls doesnotexist.html 2>/dev/null"
    res=$(eval $cmd)
    utest_z "$res" "(does not create doesnotexist.html) $cmd"
    

    cmd="./mywget www.usna.edu /i 2>&1"
    expect="HTTP/1.1 300 Multiple Choices"
    res=$(eval $cmd)
    utest "$res" "$expect" "(ERROR on multiple choices 300) $cmd"

    cmd="ls i 2>/dev/null"
    res=$(eval $cmd)
    utest_z "$res" "(does not create i) $cmd"




    echo "=== EXTRA CREDIT ==="
    rm -f batman.txt
    batman=$(echo "A\n\r" | netcat saddleback.academy.usna.edu 6666)
    cmd="./mywget saddleback.academy.usna.edu batman.txt 6666 2>/dev/null; cat batman.txt"
    res=$(eval $cmd)
    expect="$batman"
    utest "$res" "$expect" "(download file batman.txt on port 6666) $cmd"
    rm -f batman.txt

    cd ..
    echo

}
if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

test_myhost
test_mywget
