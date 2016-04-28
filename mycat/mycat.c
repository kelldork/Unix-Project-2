#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void processFile(FILE *, char* curFile);

int main(int argc, char **argv) 
{
   // bypass pass the first arg(mycat) by incrementing argv pointer  
   *argv++;
   if(argc > 1)
   {
       // cat can have any number of files to concatenate passed to it
       while(*argv)
       {
          FILE *fp = fopen(*argv, "r");
          // If the file open failed print the error message
          if(fp == NULL)
          {
            warn("%s", *argv);
          }
          else
          {
             processFile(fp, *argv);
             fclose(fp); 
          }
          *argv++;
        }
     }
     else
     {
        // Test if stdin is from the terminal.  If it is not,
        // then it is a file redirect or pipe 
        if(!isatty(STDIN_FILENO))
        {
           processFile(stdin, "-");
        }
        // Only 1 argument, and no stdin redirect, so args were missing
        else
        {
	   fprintf(stderr, "missing arguments, usage: mycat [file ...]\n");
        }
     }
}

void processFile(FILE *fp, char *curFile)
{
    int fd = fileno(fp);
    struct stat buf = {0};
    if(-1 == fstat(fd, &buf))
    {
        perror("fstat() failed");
        exit(1);
    }
    else if(S_ISDIR(buf.st_mode))
    {
       fprintf(stderr, "mycat: %s: Is a directory\n", curFile);
    }
    else
    {
       int ch;
       ch = getc(fp);
       while(ch != EOF)
       {
          putchar(ch);
          ch = getc(fp);
       }
    }
}
