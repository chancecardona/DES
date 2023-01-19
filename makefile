CC = gcc
CFLAGS=-I
DEPS = des.h

des: des.c main.c
	$(CC) -o des.o des.c main.c
