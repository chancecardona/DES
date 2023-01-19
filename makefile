CC = gcc
CFLAGS=-I.
DEPS = des.h

des: des.c main.c
	$(CC) $(CFLAGS) -o des.o des.c main.c
