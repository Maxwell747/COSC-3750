# Makefile
# Author: Maxwell SLingerland
# Date: Mar 5, 2020
#
# COSC 3750, Homework 5
#
# Makefile for Homework 5

CC = gcc
CFLAGS = -ggdb -Wall

wyls: wyls.c 
		$(CC) $(CFLAGS) wyls.c -o wyls

.PHONY: clean
		I/bin/rm -f wyls