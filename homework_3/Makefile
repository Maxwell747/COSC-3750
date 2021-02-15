##################################
# Makefile
# Maxwell Slingerland
# COSC 3750 Spring 2021
# Homework 3, Using Make
# 2/14/2021
#
# Practice using make in c files
##################################

CC = gcc
CFLAGS = -g

OBJS = prompt.o compute.o display.o

approxe: prompt.o compute.o display.o approxe.c
		$(CC) promt.o compute.o display.o approxe.c -o approxe

prompt.o: prompt.c prompt.h
		$(CC) prompt.c

compute.o: compute.c compute.h
		$(CC) compute.c

display.o: display.c display.h
		$(CC) display.c

.PHONY: clean tidy
tidy:
		I/bin/rm -f *.o

clean:
		I/bin/rm -f *.o approxe