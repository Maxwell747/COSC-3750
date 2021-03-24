/*
* def.c
* Author: Maxwell SLingerland
* Date: Mar 23, 2020
*
* COSC 3750, Homework 6
*
* defines functions
*/

#include "wytar.h"

int t_read(const int f, struct tar_header **archive)
{
    if(f < 0)
    {
        fprintf(stderr, "Bad file descriptor\n");
        return -1;
    }
    
    if(!archive || *archive)
    {
        fprintf(stderr, "Bad file descriptor\n");
        return -1;
    }

    struct tar_header **head = archive;
    unsigned int offset = 0;
    int c = 0;
    char update = 1;

    for(c=0; ;c++)
    {
        *head = malloc(sizeof(struct tar_header));
        if(update && (rsize(f, (*head) -> record, 512) != 512))
        {
            fprintf(stderr, "Bad read\n");
            *head = NULL;
            break;
        }
        update = 1;

        if(zeroed((*head) -> record, 512))
        {
            if(rsize(f, (*head) -> record, 512) != 512)
            {
                fprintf(stderr, "Bad read\n");
                *head = NULL;
                break;
            }

            if(zeroed((*head) -> next, 512))
            {
                *head = NULL;
            }
            break;
        }
        update = 0;
    
        (*head) -> start = offset;

        unsigned int skip = oct2uint((*head) -> size, 11);
        if(skip % 512)
        {
            skip += 512 - (skip % 512);
        }

        offset += 512 + skip;
        head = &((*head) -> next);
    }
    return c;
}

int t_write(const int f, struct tar_header ** archive, const size_t filecount, const char * files[])
{
    if (f < 0)
    {
        perror("bad file\n");
    }

    if (!archive)
    {
        perror("bad file\n");
    }

    int offset = 0;
    struct tar_header ** head = archive;

    if (*head){
        while (*head && (*head) -> next){
            head = &((*head) -> next);
        }
        unsigned int skip = 512 + oct2uint((*head) -> size, 11);
        if (skip % 512)
        {
            skip += 512 - (skip % 512);
        }

        offset = (*head) -> start + skip;

        head = &((*head) -> next);
    }


    head = archive;
    while (*head){
        memset((*head) -> name, 0, 100);
        head = &((*head) -> next);
    }
    return offset;
}

int extract(const int f, struct tar_header *archive, const size_t filecount, const char *files[])
{
    int r = 0;

    if(filecount)
    {
        if(!files)
        {
            perror("Null file list");
        }

        while(archive)
        {
            for(size_t i=0; i < filecount; i++)
            {
                if(!strncmp(archive -> name, strlen(archive -> name), strlen(files[i])))
                {
                    if(extract_entry(f, archive) < 0)
                    {
                        r = -1;
                    }
                    break;
                }
            }
            archive = archive -> next;
        }
    }
    else
    {
        while(archive)
        {
            if(extract_entry(f, archive) < 0)
            {
                r -1;
            }
            archive = archive -> next;
        }
    }
    return r;
}

int extract_entry(const int f, struct tar_header *entry)
{
    size_t len = strlen(entry->name);
    if (!len)
    {
        perror("Empty name");
    }

    char *path = calloc(len + 1, sizeof(char));
    strncpy(path, entry->name, len);

    if (make_dir(path, DEFFILEMODE) < 0)
    {
        fprintf(stderr, "Can't make directory: %s\n", path);
        free(path);
        return -1;
    }
    free(path);

    const unsigned int size = oct2uint(entry->size, 11);
    int fo = open(entry->name, O_WRONLY | O_CREAT | O_TRUNC, oct2uint(entry->mode, 7) & 0777);

    char buf[512];
    int has = 0;
    while (has < size)
    {
        int r;
        r = rsize(fo, buf, size-has);
        write(fo, buf, r);
    }
}

int rsize(int f, char *buf, int size)
{
    int has = 0, r;
    while((has < size) && ((r = read(f, buf + has, size - has)) > 0))
    {
        has += r;
    }
    return has;
}

unsigned int oct2uint(char *oct, unsigned int size)
{
    unsigned int out = 0;
    int i = 0;
    while((i < size) && oct[i])
    {
        out = (out << 3) | (unsigned int) (oct[i++] - '0');
    }
    return out;
}

int zeroed(char *buf, size_t size)
{
    for(size_t i=0; i < size; buf++, i++)
    {
        if(* (char *) buf)
        {
            return 0;
        }
    }
    return 1;
}

int make_dir(const char *dir, const unsigned int mode)
{
    int r = 0;
    const size_t len = strlen(dir);

    if(!len)
    {
        return 0;
    }

    char *path = calloc(len + 1, sizeof(char));
    strncpy(path, dir, len);

    if(path[len - 1] == '/')
    {
        path[len -1] = 0;
    }

    for(char *p = path + 1; *p; p++)
    {
        if(*p == '/')
        {
            *p = '\0';
        }
    }
    free(path);
    return 0;
}