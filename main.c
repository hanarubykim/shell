#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include "headers.h"

char ** parse_args(char *line, char *delimiter){
  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  while(line != NULL){
    args[i] = strsep(&line, delimiter);
    i++;
  }
  //args[i] == NULL
  return args;
}


int run_commands(char *line){
  char * cmd = malloc(64 * sizeof(char));
  strcat(cmd, line);
  char ** args = parse_args(cmd, " ");
  return 0;


}


void semicolon(char *line){
  char ** separated = parse_args(line, ";");
  int i = 0;
  int store;
  while(separated[i]){
    run_commands(separated[i]);
    i++;
  }
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

  while(strncmp(line,"EXIT\0",100) != 0){
    char ** args = parse_args(line, " ");
    execvp(args[0], args);
  }
  return 0;
}
