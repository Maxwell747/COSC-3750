/*
* wyls.c
* Author: Maxwell SLingerland
* Date: Mar 7, 2020
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
#include<stdbool.h>
#include<string.h>

void humanSize(double size) 
{
    int i = 0;
    char buf[10];
    const char* units[] = {"", "K", "M", "G"};
    while (size >= 1024 && i+1<4) {
        size /= 1024;
        i++;
    }
    sprintf(buf, "%.*f%s",i, size, units[i]);
    printf("%*s",6,buf);
}

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

void ls_n(const char *d, int h)
{
    struct dirent *files;
    struct stat stats;
    char date[50];
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
        stat(files->d_name,&stats);
        strftime(date, 50, "%b %d %H:%M", localtime(&stats.st_mtime));
        time_t rawTime;
        time(&rawTime);
        if((rawTime - stats.st_mtime) > 15552000)
        {
            strftime(date, 50, "%b %d  %Y", localtime(&stats.st_mtime));
        }
        
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
        printf("%d",stats.st_uid);
        printf(" ");
        printf("%d",stats.st_gid);
        printf(" ");
        if(h == 1)
        {
            humanSize(stats.st_size);
        }
        else
        {
            printf("%*ld",6,stats.st_size);
        }
        printf(" ");
        printf("%s",date);
        printf(" ");
        printf("%s",files->d_name);
        printf("\n");
    }
    closedir(dir);
}

int main(int argc, const char *argv[])
{
   int op_h = 0;
   int op_n = 0;
   int c = 1;
   if(argc == 1)
   {
       ls(".");
   }
   if(argc == 2)
   {
       ls(argv[argc-1]);
   }
   else if(argc > 2)
   {
      for(int i=1; i<argc; i++)
      {
          if (0 == strcmp(argv[i], "-n"))
          {
              op_n = 1;
              c += 1;
          }
          else if (0 == strcmp(argv[i], "-h"))
          {
              op_h = 1;
              c += 1;
          }
          else if (0 == strcmp(argv[i], "-nh"))
          {
              op_h = 1;
              op_n = 1;
              c += 1;
          }
          else if (0 == strcmp(argv[i], "-hn"))
          {
              op_h = 1;
              op_n = 1;
              c += 1;
          }
      }
      if(op_h == 1 && op_n == 0)
      {
          if((argc - c) == 0)
          {
              ls(".");
          }
          else
          {
              ls(argv[argc-1]);
          }
      }
      else
      {
          if((argc - c) == 0)
          {
              ls_n(".",op_h);
          }
          else
          {
              ls_n(argv[argc-1],op_h);
          }
          
      }
   }
   
   return 0;
}