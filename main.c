#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include "headers.h"

int main(int argc, char **argv){
  char *line;
  char **args;
  int status;

  char command[1000];
  if(argc <= 1){
    printf("Enter command: ");
    fgets(command, 1000, stdin);
  }else{
    strcpy(command, argv[1]);
  }

  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  while(line != NULL){
    args[i] = strsep(&line, " ");
    i++;
  }
  args[i] = NULL;
  return args;
  run_shell();
  return 0;
}

void run_shell(){
  char *line;
  char **args;
  int status;

  line = read();
  args = parse(line);
  status = execute(args);
}

char read(){

}

char ** parse(char *line){
  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  while(line != NULL){
    args[i] = strsep(&line, " ");
    i++;
  }
  args[i] = NULL;
  return args;
}
