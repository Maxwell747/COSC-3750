/*
* wyls.c
* Author: Maxwell SLingerland
* Date: Mar 5, 2020
*
* COSC 3750, Homework 5
*
* This is a simple version of the ls utility. It is designed to
* print out the files of the directory
* and information on those files
*/

#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include <inttypes.h>

void ls(const char *d)
{
    struct dirent *files;
    DIR *dir = opendir(d);
    if(dir == NULL)
    {
       perror("Unable to read directory");
    }
    while((files = readdir(dir)) != NULL)
    {
        if(files->d_name[0] == '.')
        {
            continue;
        }
        printf("%s\n", files->d_name);
    }
    closedir(dir);
}

void ls_n(const char *d)
{
    struct dirent *files;
    struct stat stats;
    DIR *dir = opendir(d);
    if(dir == NULL)
    {
       perror("Unable to read directory");
    }
    while((files = readdir(dir)) != NULL)
    {
        if(files->d_name[0] == '.')
        {
            continue;
        }
        char date[100] = "";
        strftime(date, 100, "%m %d %H:%M", localtime(stats.st_mtime));
        printf( (S_ISDIR(stats.st_mode)) ? "d" : "-");
        printf( (stats.st_mode & S_IRUSR) ? "r" : "-");
        printf( (stats.st_mode & S_IWUSR) ? "w" : "-");
        printf( (stats.st_mode & S_IXUSR) ? "x" : "-");
        printf( (stats.st_mode & S_IRGRP) ? "r" : "-");
        printf( (stats.st_mode & S_IWGRP) ? "w" : "-");
        printf( (stats.st_mode & S_IXGRP) ? "x" : "-");
        printf( (stats.st_mode & S_IROTH) ? "r" : "-");
        printf( (stats.st_mode & S_IWOTH) ? "w" : "-");
        printf( (stats.st_mode & S_IXOTH) ? "x" : "-");
        printf(" ");
        //printf("%s",getpwnam(stats.st_uid));
        printf(" ");
        printf("%s",getgrnam(stats.st_gid));
        printf(" ");
        printf("%d",stats.st_size);
        printf(" ");
        printf("%s",date);
        printf(" ");
        printf("%s",files->d_name);
        printf("\n");
    }
    closedir(dir);
}
/*
const char humanSize(uint64_t size)
{
	char *suffix[] = {"", "KB", "MB", "GB"};
	char length = sizeof(suffix) / sizeof(suffix[0]);

	int i = 0;
	double dblBytes = size;

	if (size > 1024) 
    {
		for (i = 0; (size / 1024) > 0 && i<length-1; i++, size /= 1024)
			dblBytes = size / 1024.0;
	}

	static char output[200];
	sprintf(output, "%.02lf %s", dblBytes, suffix[i]);
	return output;
}*/

int main(int argc, const char *argv[])
{
   
   if(argc == 1)
   {
       ls(".");
   }
   else if(argc >= 2)
   {
       if(argv[1][0] == '-')
       {
           ls_n(".");
       }
       else
       {
           ls(argv[1]);
       }
   }
   return 0;
}