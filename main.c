#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include "headers.h"

char ** parse_args(char *line){
  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  while(line != NULL){
    args[i] = strsep(&line, " ");
    i++;
    printf("args[%d]: %s", i, args[i]);
  }
  args[i] = NULL;
  return args;
}

int main(int argc, char *argv[]){
  char command[1000];
  char *line = command;
  if (argc <= 1){
    printf("Enter command: ");
    fgets(line, 1000, stdin);
    line[strlen(line) - 1] = '\0';
  }
  else{
    strcpy(line, argv[1]);
  }

  while(line != "EXIT\0"){
    char ** args = parse_args(line);
    execvp(args[0], args);
  }
  return 0;
}

// void run_shell(char *line){
//   char **args;
//   int status;
//
//   args = parse(line);
//   status = execute(args);
// }
