

test: listTest.c list.c list.h node.c node.h
	gcc -Wall listTest.c list.c node.c -o listTest