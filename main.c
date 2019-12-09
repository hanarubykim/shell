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
  return args;
}


int run_commands(char *line){
  char * cmd = malloc(64 * sizeof(char));
  strcat(cmd, line);
  char ** args = parse_args(cmd, " ");

  pid_t pid;
  pid = fork();
  if(pid == 0){
    // pid == 0 means child process created
    // getpid() returns process id of calling process
    int error = execvp(args[0], args);
    if (error == -1)
      printf("%s: %s\n", args[0], strerror(errno));
    exit(0);
  }
  int cpid = wait(NULL);
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
  while(1){
    char command[1000];
    char *line = calloc(100, sizeof(char));
    printf("Enter command: ");
    fgets(line, 1000, stdin);
    line[strlen(line) - 1] = '\0';

    if(strlen(line) > 0){
      if(strncmp(line, "EXIT\0", 100) != 0){
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
