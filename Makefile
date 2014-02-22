CFLAGS=-lm

line: line.c lib.c
	gcc -lm line.c lib.c -o line
