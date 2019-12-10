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

// char ** parse_args(char *line, char *delimiter){
//   char ** args = malloc(64 * sizeof(char));
//   int i = 0;
//   while(line != NULL){
//     args[i] = strsep(&line, delimiter);
//     i++;
//   }
//   return args;
// }

char ** parse_args(char *line, char *delimiter){
  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  char * temp;
  while(line != NULL){
    temp = strsep(&line, delimiter);
    if (strcmp(temp,"")) {
      args[i] = temp;
      i++;
    }
  }
  return args;
}


void semicolon(char *line){
  char ** separated = parse_args(line, ";");
  int i = 0;
  while(separated[i]){
      run_commands(separated[i]);
    i++;
  }
}

int redir_input(char *line){
  char ** separated = parse_args(line, "<");
  int fd = STDIN_FILENO;
  int fd1 = -1;
  int i = 1;
  while(separated[i] != NULL){
    fd1 = open(separated[i], O_RDONLY);
    int num = dup2(fd1, fd);
    if(fd1 == -1){
      //error
      printf("Uh oh! %s\n", strerror(errno));
    }
    close(fd);
    i++;
  }
  return 0;
}

int redir_output(char *line){
  char ** separated = parse_args(line, ">");
  int i = 1;
  int fd = STDOUT_FILENO;
  int fd1 = -1;
  while(separated[i] != NULL){
    fd1 = open(separated[i], O_WRONLY | O_CREAT, 0644);
    int num = dup2(fd1, fd);
    if(fd1 == -1){
      //error
      printf("Uh oh! %s\n", strerror(errno));
    }
    close(fd);
    i++;
  }
  return 0;
}



int run_commands(char *line){
  char * cmd = malloc(64 * sizeof(char));
  strcat(cmd, line);
  char ** args = parse_args(cmd, " ");

  pid_t pid;
  pid = fork();

  int i;

  if(pid == 0){
    // pid == 0 means child process created
    // getpid() returns process id of calling process

    //************************* DOES NOT WORK (YET!) ***********************
    // redir_output(line);
    // redir_input(line);


    int error = execvp(args[0], args);
    if (error == -1)
      printf("%s: %s\n", args[0], strerror(errno));
    exit(0);
  }
  int cpid = wait(NULL);
  return 0;

}

int main(int argc, char *argv[]){
  while(1){
    char command[1000];
    char *line = calloc(100, sizeof(char));
    printf("Enter command: ");
    fgets(line, 1000, stdin);
    line[strlen(line) - 1] = '\0';

    if(strlen(line) > 0){
      char * check = &line[0];
      if(strncmp(check, ";", 0) || strncmp(check, "<", 0) || strncmp(check, ">", 0) || strncmp(check, "|", 0)){
        printf("Doesn't look right.\n");
        exit(0);
      } else if(strchr(line, ';')){
        semicolon(line);
      } else if(strncmp(line, "EXIT\0", 100) != 0){
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
