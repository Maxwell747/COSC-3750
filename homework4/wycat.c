/*
* wycat.c
* Author: Maxwell SLingerland
* Date: Feb 21, 2020
*
* COSC 3750, Homework 4
*
* This is a simple version of the cat utility. It is designed to
* print out the contents of file or
* read and write lines of standard input
*/

#include <stdio.h>
#include <string.h>

void inputOutput()
{
    char str[100];
    for(;;)
    {
        char input = scanf(" %s", str);
        if(input == EOF)
        {
        break;
        }
        else
        {
            printf("%s \n", str);
        }
    }
}

int main(int argc, char* argv[])
{
    char buffer[4096];
    FILE *fptr;

    if(argc == 1) //no arguments
    {
        inputOutput();
    }

    if(argc >= 2)
    {
        for(int i=0; i<argc; i++)
        {
            if (0 == strcmp(argv[i], "-"))
            {
                inputOutput();
            }
            else
            {
                fptr = fopen(argv[i], "r");
                if(fptr == NULL)
                {
                    printf("Can't open file: %s \n", argv[i]);
                }
                else
                {
                    fread(&buffer, sizeof(char), 4096, fptr);
                    printf("%s \n", buffer);
                    fclose(fptr);
                }
            }

        }
    }

}