#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void processFile(FILE *);

int main(int argc, char **argv) 
{
   if(argc > 1)
   {
       // bypass pass the first arg(mycat) by incrementing argv pointer  
       *argv++;
       // cat can have any number of files to concatenate passed to it
       while(*argv)
       {
          FILE *fp = fopen(*argv, "r");
          // If the file doesn't exist print the message
          if(fp == NULL)
          {
            warn("%s", *argv);
          }
          else
          {
             processFile(fp);
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
           processFile(stdin);
        }
        // Only 1 argument, and no stdin redirect, so args were missing
        else
        {
	   fprintf(stderr, "missing arguments, usage: mycat [file ...]\n");
        }
     }
}

void processFile(FILE *fp)
{
    int ch;
    ch = getc(fp);
    while(ch != EOF)
    {
       putchar(ch);
       ch = getc(fp);
    }
}
