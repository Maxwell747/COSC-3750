# Makefile
# Author: Maxwell SLingerland
# Date: Apr 2, 2020
#
# COSC 3750, Homework 7
#
# Makefile for Homework 7

CC = gcc
CFLAGS = -ggdb -Wall

wytalk: wytalkC.c wytalkD.c socketfun.c socketfun.h
		$(CC) $(CFLAGS) wytalkC.c socketfun.c -o wytalkC
		$(CC) $(CFLAGS) wytalkD.c socketfun.c -o wytalkD

.PHONY: clean
clean:
		rm -f wytalkC wytalkD