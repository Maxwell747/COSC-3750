# Makefile
# Author: Maxwell SLingerland
# Date: Mar 22, 2020
#
# COSC 3750, Homework 6
#
# Makefile for Homework 6

CC = gcc
CFLAGS = -ggdb -Wall

OBJS = def.o

wytar: def.o wyls.c wytar.h 
		$(CC) $(CFLAGS) def.o wytar.c -o wytar

def.o: def.c wytar.h
		$(CC) $(CFLAGS) def.c

.PHONY: clean
clean:
		rm -f wytar *.o