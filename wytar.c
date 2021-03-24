/*
* wytar.c
* Author: Maxwell SLingerland
* Date: Mar 23, 2020
*
* COSC 3750, Homework 6
*
* simple tar utility implementation
*/

#include <stdio.h>
#include "wytar.h"

int main(int argc, char *argv[])
{
    char c=0, x=0;

    for(int i=0; argv[2][i]; i++)
    {
        switch(argv[2][i])
        {
            case 'c': c=1; break;
            case 'x': x=1; break;
            default:
                perror("Argument cannot be opned or accessed: %c\n", argv)[2][i];
                break;
        }
    }

    const char inputs = c + x;
    if(inputs > 1)
    {
        fprintf(stderr, "Can't have both 'c' and 'x' options\n");
        return -1;
    }
    else if(inputs < 1)
    {
        fprintf(stderr, "Must have either 'c', 'x' option");
        return -1;
    }

    if(0 != strcmp(argv[3], "-f"))
    {
        fprintf(stderr, "Must have 'f' option");
        return -1;
    }

    int r=0;
    int fd=-1;
    const char *filename = argv[4];
    const char **files = (const char **) &argv[5];
    struct tar_header *archive = NULL;

    if(c)
    {
        if((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
        {
            fprintf(stderr, "Unable to open file %s\n", filename);
            return -1;
        }
        if(tar_write(fd, &archive, argc, files) < 0)
        {
            r = -1;
        }
    }
    else
    {
        if((fd = open(filename, O_RDWR)) < 0)
        {
            fprintf(stderr, "Unable to open file %s\n", filename);
            return -1;
        }

        if(t_read(fd, &archive) < 0)
        {
            close(fd);
            return -1;
        }

        if(x)
        {
            extract(fd, archive, argc, files);
        }
        else
        {
            fprintf(stderr, "Couldn't perform action\n");
            r = -1;
        }
    }
    close(fd);
    return r;
}