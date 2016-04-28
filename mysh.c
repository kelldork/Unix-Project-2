#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "mycat.h"

#define MAX_BUFF 1024
#define MAX_ARGS 64
#define SEPARATOR " \t\n"

int mycat(char * argv);

int main(int argc, char ** argv) {
  char buf[MAX_BUFF];
  char line[MAX_BUFF];
  char nwd[MAX_BUFF];
  char prompt[MAX_BUFF];
  char * args[MAX_ARGS];
  char ** arg;
  struct passwd *pwd;
  struct stat uid;

  while(!feof(stdin)) {

    //prompt - uid:/path/$
    getcwd(prompt, sizeof(prompt));
    pwd = getpwuid(uid.st_uid);
    printf("%s:%s$ ", pwd->pw_name, prompt);

    if(fgets(line, MAX_BUFF, stdin)) {

      arg = args;
      *arg++ = strtok(line, SEPARATOR);

      while ((*arg++ = strtok(NULL, SEPARATOR)));

      if (args[0]) {

        //clear screen
        if(!strcmp(args[0], "clear")) {
          printf("\e[1;1H\e[2J");
        }

        //mycat
        else if(!strcmp(args[0], "mycat")) {
          if(!args[1]) printf("mycat: %s: No such file or directory\n", args[1]);
          else mycat(args[1]);
        }

        //mycd
        else if(!strcmp(args[0], "mycd")) {
          if(!strcmp(args[1], ".")) {
            chdir(".");
          }
          else if(!strcmp(args[1], "..")) {
            chdir("..");
          }
          else {
            if(chdir(args[1]) != 0) {
              printf("-bash: mycd: %s: No such file or directory\n", args[1]);
            }
            else {
              chdir(args[1]);
            }
          }
        }

        //pwd
        else if(!strcmp(args[0], "pwd")) printf("%s\n", prompt);

        //exit
        else if(!strcmp(args[0], "exit")) break;

        //wrong command
        else printf("%s: command not found\n", args[0]);
      }
    }
  }
  return 0;
}
