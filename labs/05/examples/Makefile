

all: isdir printmode printusername printgroupname printtime

isdir: isdir.c
	clang isdir.c -o isdir

printmode: printmode.c
	clang -lbsd printmode.c -o printmode

printusername: printusername.c
	clang printusername.c -o printusername

printgroupname: printgroupname.c
	clang printgroupname.c -o printgroupname

printtime: printtime.c
	clang printtime.c -o printtime


clean:
	rm -f isdir printmode printusername printgroupname printtime *~