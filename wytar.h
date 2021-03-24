/*
* struct.h
* Author: Maxwell SLingerland
* Date: Mar 22, 2020
*
* COSC 3750, Homework 7
*
* tar data structure
*/
#ifndef _WYTAR_
#define _WYTAR_

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <sys/sysmacros.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

struct tar_header
{                       /* byte offset */
    char name[100];     /* 0 */
    char mode[8];       /* 100 */
    char uid[8];        /* 108 */
    char gid[8];        /* 116 */
    char size[12];      /* 124 */
    char mtime[12];     /* 136 */
    char chksum[8];     /* 148 */
    char typeflag;      /* 156 */
    char linkname[100]; /* 157 */
    char magic[6];      /* 257 */
    char version[2];    /* 263 */
    char uname[32];     /* 265 */
    char gname[32];     /* 297 */
    char devmajor[8];   /* 329 */
    char devminor[8];   /* 337 */
    char prefix[155];   /* 345 */
    char pad[12];       /* 500 */
    char record[512];
    unsigned int start;
    struct tar_header *next;
};

int make_dir(const char *dir, const unsigned int mode);

int t_read(const int f, struct tar_header **archive);

int t_write(const int f, struct tar_header ** archive, const size_t filecount, const char * files[]);

int extract(const int f, struct tar_header *archive, const size_t filecount, const char *files[]);

int extract_entry(const int f, struct tar_header *entry);

int rsize(int f, char *buf, int size); 

unsigned int oct2uint(char *oct, unsigned int size);

int zeroed(char *buf, size_t size);

int make_dir(const char *dir, const unsigned int mode);

#endif