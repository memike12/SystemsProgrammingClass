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


function test_primes(){
    echo "--- TEST PRIMES ---"

    cd primes
    make clean >/dev/null 2>/dev/null
    make >/dev/null 2>/dev/null
   
    cmd="./factor 53332388942191969"
    res=$(eval $cmd)
    expect="Factor: 230938063"
    utest "$res" "$expect" "(factor properly) $cmd"

    cmd="./factor 3"
    res=$(eval $cmd)
    expect="Prime: 3"
    utest "$res" "$expect" "(Identify small prime) $cmd"

    cmd="./factor 903332388942191977"
    res=$(eval $cmd)
    expect="Prime: 903332388942191977"
    utest "$res" "$expect" "(Identify BIG prime) $cmd"


    cmd="python -c \"print 1 if ($(/usr/bin/time -f time:%E ./slow_factor 53332388942191969 2>&1 | grep time | cut -d : -f 3) - $(/usr/bin/time -f time:%E ./factor 53332388942191969 2>&1 | grep time | cut -d : -f 3)) > 1.0 else 0\""
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(find factor runs much faster) $cmd ($res)"

    cmd="python -c \"print 1 if ($(/usr/bin/time -f time:%E ./slow_factor 93332388942192053 2>&1 | grep time | cut -d : -f 3) - $(/usr/bin/time -f time:%E ./factor 93332388942192053 2>&1 | grep time | cut -d : -f 3)) > 1.0 else 0\""
    res=$(eval $cmd)
    expect="1"
    utest "$res" "$expect" "(find prime runs much faster) $cmd ($res)"

    cd ..
    echo
}

function test_socket_server(){
    echo "--- TEST SOCKET SERVER ---"
    echo "[ if you see \"bind: Address already in use\", wait 1 minute and try again ]"
    cd socket-server

    make clean >/dev/null 2>/dev/null
    sed "s/int main(){/int main(){setvbuf(stdout, NULL,_IONBF, 0);/" threaded_server.c | clang -xc -lpthread - -o threaded_server


    killall threaded_server 2>/dev/null
    rm -f output.txt nc.1.txt nc.2.txt nc.3.txt
    ./threaded_server > output.txt &
    server_pid=$!

    sleep 1

    echo "testing 1" | netcat localhost 1845 > nc.1.txt &
    echo "testing 2" | netcat localhost 1845 > nc.2.txt &
    echo "testing 3" | netcat localhost 1845 > nc.3.txt &

    sleep 1

    cat <<EOF > runner.sh
#!/bin/bash
for i in \$(seq 1 1 100)
do
echo "loop" | netcat localhost 1845 | netcat localhost 1845 | netcat localhost 1845 > /dev/null
done
EOF
    chmod +x runner.sh
    ./runner.sh & 

    cmd="[ \"\$(ps -aL | grep \"threaded_server\" | wc -l)\" -gt 1 ]; echo $?"
    res=$(eval $cmd)
    expect="0"
    utest "$res" "$expect" "(starts threads) $cmd ($res)"

    cmd="grep \"testing 1\" nc.1.txt"
    res=$(eval $cmd)
    utest_nz "$res" "(Echos properly) $cmd"

    cmd="grep \"testing 2\" nc.2.txt"
    res=$(eval $cmd)
    utest_nz "$res" "(Echos properly) $cmd"

    cmd="grep \"testing 3\" nc.3.txt"
    res=$(eval $cmd)
    utest_nz "$res" "(Echos properly) $cmd"
    
    killall threaded_server 2>/dev/null
    killall runner.sh 2>/dev/null
    rm -f output.txt nc.1.txt nc.2.txt nc.3.txt runner.sh
    cd ..
    echo

}
if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

test_primes
test_socket_server
