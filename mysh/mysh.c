#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUFF 1024
#define MAX_ARGS 64
#define SEPARATOR " \t\n"

/**
This only works if the executables are in the same directory
as mysh.  In order to support paths we would have to parse
detect myls, mycat, or mycp was being called in the shell
even if someone types ../bin/mycat for example **/

void executeProgram(char **args);

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
        else if(!strcmp(args[0], "mycat")) executeProgram(args);

        //mycp
        else if(!strcmp(args[0], "mycp")) executeProgram(args);

        //myls
        else if(!strcmp(args[0], "myls")) executeProgram(args);

        //mycd
        else if(!strcmp(args[0], "mycd")) { 
          if(args[1]) {
            if(chdir(args[1]) != 0) printf("-bash: mycd: %s: No such file or directory\n", args[1]);
          }
          else chdir(getenv("HOME"));
        }
	
        //mypwd
        else if(!strcmp(args[0], "mypwd")) printf("%s\n", prompt);

        //exit
        else if(!strcmp(args[0], "exit")) break;

        //wrong command
        else fprintf(stderr, "%s: command not found\n", args[0]);
      }
    }
  }
  return 0;
} 

void executeProgram(char **args)
{
   pid_t pid=fork();
   if(pid == 0)
   {
<<<<<<< HEAD
      char command[256];
	  /***********************************************/
	  /*  THIS LINE NEEDS TO BE ALTERED AS NEEDED    */
	  /***********************************************/
	  strcat(command, "/home/Students/klk2/unix/proj2_final/Unix-Project-2/");
	  //strcat(command, "/home/Students/amd166/Unix/Unix-Project-2/");
	  //strcat(command, "/home/Students/klk2/Unix/Unix-Project-2/");
	  strcat(command, args[0]);
      int res = execv(command, args);
=======
      //char command[256];
	  /**************************************************/
	  /* THIS LINE NEEDS TO BE ALTERED FOR EACH MACHINE */
	  /**************************************************/
	  //strcat(command, "/home/Students/scm84/Unix/Unix-Project-2/");
	  //strcat(command, args[0]);
      int res = execv(args[0], args);
>>>>>>> 0edca2ee899719246a4f7cb2b65bd69369fa651d
      fprintf(stderr, "execv result %i failed with errno %d\n", res, errno);
      //errno 2 is no such file or directory 
      if(errno == 2)
      {
         fprintf(stderr, "Make sure %s is in the same directory as mysh\n", args[0]);
      }
      exit(127);
   }
   else if(pid > 0)
   {
      // wait for child to exit
      waitpid(pid, 0, 0);
   }
   else
   {
      fprintf(stderr, "error, child1 fork failed\n");
   }
}
