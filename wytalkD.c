/*
* wytalkD.c
* Author: Maxwell SLingerland
* Date: Apr 2, 2020
*
* COSC 3750, Homework 7
*
* server side
* open a socket on port 51100
* accept connection
* print out recieved data
* start before wytalkC.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "socketfun.h"

int main()
{
    char hn[256];
    int sock, fd;
    char buf[1000];
    FILE *fin, *fout;

    gethostname(hn, sizeof(hn));
    sock = serve_socket(hn, 51100);
    fd = accept_connection(sock);

    fin = fdopen(fd, "r");
    fout = fdopen(fd, "w");

  
    while (1)
    {
        if(fgets(buf, 1000, fin) == NULL)
        {
            exit(0);
        }
        fputs(buf, stdout);
        fflush(stdout);

        if(fgets(buf, 1000, stdin) == NULL)
        {
            exit(0);
        }
        fputs(buf, fout);
        fflush(fout);
    }
    return 0;
}