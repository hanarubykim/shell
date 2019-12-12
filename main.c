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

char ** parse_args(char *line, char *delimiter){
  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  char * temp;
  while(line != NULL){
    temp = strsep(&line, delimiter);
    if(strcmp(temp,"")){
      args[i] = temp;
      i++;
    }
  }
  return args;
}

char * fixws(char *arg){
  char * ws = " ";
  while(strcmp(arg, ws) == 0){
      arg++;
  }
  int index = -1;
  int i = 0;
  while(strcmp(arg, ws) != 0){
    arg++;
  }
  *arg = '\0';

  return arg;
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
  while(separated[i]){
    fd1 = open(fixws(separated[i]), O_RDONLY);
    int num = dup2(fd1, fd);
    if(fd1 == -1){
      printf("Uh oh! %s\n", strerror(errno));
    }
    close(fd1);
    i++;
  }
  return 0;
}

int redir_output(char *line){
  char ** separated = parse_args(line, ">");
  int i = 1;
  int fd = STDOUT_FILENO;
  int fd1 = -1;
  while(separated[i]){
    redir_input(separated[i]);
    fd1 = open(fixws(separated[i]), O_WRONLY | O_CREAT, 0644);
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

// void call_cd(char *line){
//   printf("REACHES THIS POINT\n");
//   int change;
//   change = chdir(line);
//   if(change == -1){
//     printf("ERROR: %s\n", strerror(errno));
//   }
// }


//line is the targeted string
//target is the character you want to change
//newStr is the string you want to replace it with
//HELPER FUNCTION FOR CD
char* strReplace(char* line, char target, char* newStr) {
  char* temp = calloc(sizeof(char), 1000);
  char* point = strchr(line, target);
  *point = 0;
  point++;
  strcat(temp, line);
  strcat(temp, newStr);
  strcat(temp, point);
  printf("%s\n", temp);

  int index = 0;
  while (temp[index++]);
  char* output = calloc(sizeof(char), index);
  strcpy(output, temp);

  free(temp);

  return output;
}

void call_cd(char ** args){
  int n;
  if (!strcmp(args[0], "cd")){
    n = chdir(args[1]);
    if (args[1] == NULL) {
      n = chdir(getenv("HOME"));
    }
    else if (strchr(args[1], '~') != NULL){
      char * home = strReplace(args[1], '~', getenv("HOME"));
      n = chdir(home);
    }
    if (n == -1){
      printf("Uh oh! cd error: %s", strerror(errno));
    }
  }
  if (!strcmp(args[0], "exit")){
    exit(0);
  }
}


int run_commands(char *line){
  char * currentdirectory = malloc(256);
  char * cmd = malloc(64 * sizeof(char));
  strcat(cmd, line);
  char ** args = parse_args(cmd, " ");

  if (!strcmp(args[0], "cd")){
    call_cd(args);
    return 0;
  }

  pid_t pid;
  pid = fork();

  int fd1 = -1;

  if(pid == 0){
    // pid == 0 means child process created
    // getpid() returns process id of calling process

    //************************* DOES NOT WORK (YET!) ***********************
    redir_output(line);
    redir_input(line);

    int error = execvp(args[0], args);
    if (error == -1)
    printf("%s: %s\n", args[0], strerror(errno));
    exit(0);
  }

  int cpid = wait(NULL);
  return 0;
}


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

// char ** args = parse_args(line, " ");
//
// if(strcmp(args[0], "cd") == 0){
//   chdir(args[1]);
// } else if(strchr(line, ';')){
//   semicolon(line);
// } else if(strncmp(line, "exit\0", 100) != 0){
//   run_commands(line);
// }
// else{
//   printf("Bye bye!\n");
//   exit(0);
// }
