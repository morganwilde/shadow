CFLAGS=-lm

line: line.c lib.c
	gcc -lm -fnested-functions line.c lib.c -o line
