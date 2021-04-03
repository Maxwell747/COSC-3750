/*
* wytalkC.c
* Author: Maxwell SLingerland
* Date: Apr 2, 2020
*
* COSC 3750, Homework 7
*
* client side
* take single command line argument(name of the host that wytalkD is on)
* request connection to port 51100 on that host
* send user input to wytalkD
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "socketfun.h"

int main(int argc, char **argv)
{
    char *hn;
    int fd;
    char buf[1000];
    FILE *fin, *fout;

    hn = argv[1];

    fd = request_connection(hn, 51100);

    fin = fdopen(fd, "r");
    fout = fdopen(fd, "w");

    while (1)
    {
        if(fgets(buf, 1000, stdin) == NULL)
        {
            exit(0);
        }
        fputs(buf, fout);
        fflush(fout);

        if(fgets(buf, 1000, fin) == NULL)
        {
            exit(0);
        }
        fputs(buf, stdout);
        fflush(stdout);
    }
    return 0;
}