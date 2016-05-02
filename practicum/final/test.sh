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


function test_shell(){
    echo "--- TEST PERMISSIONS ---"
    
    cd shell

    cmd="ls script.sh"
    res=$(eval $cmd)
    utest_nz "$res" "(copied script.sh) $cmd"

    cmd="ls -l script.sh | cut -d \" \" -f 1 | grep x"
    res=$(eval $cmd)
    utest_nz "$res" "(executable) $cmd"
    
    cmd="./script.sh | base64"
    res=$(eval $cmd)
    expect=$(cat<<EOF 
CiAgICAgICAgICAgICAgIEhBTkcgSU4gVEhFUkUgIAogICAgICAgICAgICAgICAgICwuICAgICAs
LgogICAgICAgICAgICAgICAge14gXC0iLS8gXn0KICAgICAgICAgICAgICAgICIgICBNTU0gICAi
CiAgICAgICAgICAgICAgIHsgPE8+IF8gPE8+IH0KICAgICAgICAgICAgICAgPT1fIC46WTouIF89
PQogICAgICAgICAgICAgLiIiICBgLS1eLS0nICIiLgogICAgICAgICAgICAoLH4tfi4iIiAiIiAs
fi1+LikKICAgICAgLS0tLS0tKCAgICAgKS0tLS0oICAgICApLS0tLS0KICAgICAgICAgICAgXi0n
LSctXiAgICBeLSctJy1eCiAgICAgIF9fX19fX19fX19fX19fX19fX19fX19fX19fX19fCiAgICAg
ICAgICAgIHxNTU0gIC9+Ll4uflwgIE1NTXwKICAgICAgICAgICAgLGktaS1pICgiIiggIGktaS1p
LgogICAgICAgICAgICAobyBvIG8gKSkiIikoIG8gbyBvKQogICAgICAgICAgICAgXChfKSAvKCIi
KCAgXCAoXykvCiAgICAgICAgICAgICAgYC0tJyAgXCIiXCAgYC0tJwogICAgICAgICAgICAgICAg
ICAgICApIiIpCiAgICAgICAgICAgICAgICAgICAgKCIiLwogICAgICAgICAgICAgICAgICAgICBg
Igo=
EOF
)
    utest "$res" "$expect" "(decode secrete with base64) $cmd"

    cd ..
    echo
}

function test_pipes(){
    echo "--- TEST PIPES ---"
    
    cd pipes

    make clean > /dev/null 2>/dev/null
    make > /dev/null 2>/dev/null
    
    sleep 1 && killall reverser 2>/dev/null &
    cmd="timeout 1 ./reverser < GoNavy.txt | tr \"\\\\n\" \" \"; echo -ne \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="Child: Beat Army!  Parent:  !ymrA taeB 0"
    utest "$res" "$expect" "(widows properly, Go Navy!) $cmd"

    sleep 1 && killall reverser 2>/dev/null &
    cmd="timeout 1 ./reverser < BeatArmy.txt | tr \"\\\\n\" \" \"; echo -ne \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="Child: Go Navy!  Parent:  !yvaN oG 0"
    utest "$res" "$expect" "(widows properly, Beat Army!) $cmd"

    sleep 1 && killall reverser 2>/dev/null &
    cmd="echo -n \"Hello\" | timeout 1 ./reverser | tr \"\\\\n\" \" \"; echo -ne \$?"
    res=$(eval $cmd | tr "\n" " ")
    expect="Child: Hello Parent: olleH 0"
    utest "$res" "$expect" "(widows properly, Beat Army!) $cmd"

    cd ..
    echo
}

function test_sockets(){
    echo "--- TEST SOCKETS ---"
    
    cd sockets


    make clean > /dev/null 2>/dev/null
    make > /dev/null 2>/dev/null

    killall proxy 2>/dev/null
    rm -f output.txt
    ./proxy www.usna.edu 80 > output.txt &
    proxy_pid=$!

    sleep 1
    sleep 1 && killall netcat 2>/dev/null &
    cmd="echo -e \"GET /index.html HTTP\\\\1.0\\\\n\\\\r\" | netcat localhost 1845"
    res=$(eval $cmd | tr "\n" " ")
    utest_nz "$res" "(returns results) $cmd"

    sleep 1 && killall netcat 2>/dev/null &
    cmd="echo -e \"GET /Users/cs/aviv/classes/ic221/s14/cal.html HTTP\\\\1.0\\\\n\\\\r\" | netcat localhost 1845"
    res=$(eval $cmd | tr "\n" " ")
    expect=$(echo -e "GET /Users/cs/aviv/classes/ic221/s14/cal.html HTTP\1.0\n\r" | netcat www.usna.edu 80 | tr "\n" " ")
    utest "$res" "$expect" "(all results) $cmd"

    kill "$proxy_pid" 2>/dev/null 1>/dev/null
    
    cmd="timeout 1 echo \"\$(grep -roh \"(4)\" output.txt  | wc -l) \$(grep -roh \"(5)\" output.txt  | wc -l)\""
    res=$(eval $cmd)
    expect="2 2"
    utest "$res" "$expect" "(closes sockets) $cmd"

    ./proxy www.usna.edu 8000 > output.txt 2> error.txt&
    proxy_pid=$!
    
    sleep 1
    
    sleep 1 && killall netcat 2>/dev/null &
    echo -e "GET /index.html HTTP\1.0\n\r" | netcat localhost 1845 2>/dev/null >/dev/null
    
    kill "$proxy_pid" 2>/dev/null 1>/dev/null

    cmd="grep \"Connection refused\" error.txt"
    res=$(eval $cmd)
    utest_nz "$res" "(checks connect errors) $cmd"
    

    rm -f output.txt error.txt

    cd ..
    echo
    
}

function test_threads(){
    echo "--- TEST SOCKETS ---"
    
    cd threads
    
    make clean > /dev/null 2>/dev/null
    make > /dev/null 2>/dev/null

    
    cmd="./transactions  | cut -d \":\" -f 2 | uniq | wc -l"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(random 1 consistent) $cmd"

    cmd="./transactions  | cut -d \":\" -f 2 | uniq | wc -l"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(random 2 consistent) $cmd"

    cmd="./transactions  | cut -d \":\" -f 2 | uniq | wc -l"
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(random 3 consistent) $cmd"
 
    sed "s/srandom(time(NULL))/srandom(0)/" transactions.c | clang -xc -lpthread - -o transactions
 
    cmd="./transactions  | tr \"\\\\n\" \" \" "
    res=$(eval $cmd)
    expect=" Balance: 23228 Exp. Bal: 23228 "
    utest "$res" "$expect" "(seeded 1 consistent) $cmd"

    sed "s/srandom(time(NULL))/srandom(1024)/" transactions.c | clang -xc -lpthread - -o transactions
 
    cmd="./transactions  | tr \"\\\\n\" \" \" "
    res=$(eval $cmd)
    expect=" Balance: -33934 Exp. Bal: -33934 "
    utest "$res" "$expect" "(seeded 2 consistent) $cmd"

    make clean > /dev/null 2>/dev/null
    make > /dev/null 2>/dev/null


    cd ..
    echo
    
}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

test_shell
test_pipes
test_sockets
test_threads

