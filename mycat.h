#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void processFile(FILE *);

int mycat(char *argv)
{
  FILE *fp = fopen(argv, "r");

  // If the file doesn't exist print the message
  if(fp == NULL)
  {
    //warn("%s", *argv);
    printf("mycat: %s: No such file or directory\n", argv);
  }
  else
  {
    processFile(fp);
    fclose(fp);
  }

  *argv++;
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
