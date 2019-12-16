#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "headers.h"

int main(int argc, char *argv[]){
  char * currentdirectory = malloc(256);

  while(1){
    char command[1000];
    char *line = calloc(100, sizeof(char));
    printf("(**OUR SHELL BABY**) %s", getcwd(currentdirectory, 256));
    printf("$ ");
    fgets(line, 1000, stdin);
    line[strlen(line) - 1] = '\0';

    if(strlen(line) > 0){
      char * check = &line[0];
      if(strncmp(check, ";", 0) || strncmp(check, "<", 0) || strncmp(check, ">", 0) || strncmp(check, "|", 0)){
        printf("Doesn't look right.\n");
        exit(0);
      } else if(strchr(line, ';')){
        semicolon(line);
      } else if(strncmp(line, "exit\0", 100) != 0){
        run_commands(line);
      }
      else{
        printf("Bye bye!\n");
        exit(0);
      }

      free(line);
    }
  }
  return 0;
}
