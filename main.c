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

char * fixws(char *arg){
  char * result = calloc(100, sizeof(char));
  strcpy(result, arg);
  char ws = ' ';
  int i = 0;
  int len = strlen(arg) - 1;

  while(arg[i] == ws){
      i++;
      result++;
  }

  while(arg[len] == ws){
    len--;
  }

  result[len + 1] = '\0';
  return result;
}

char ** parse_args(char *line, char *delimiter){
  char ** args = malloc(64 * sizeof(char));
  char * fixed;
  fixed = fixws(line);
  int i = 0;
  char * temp;
  while(fixed != NULL){
    temp = strsep(&fixed, delimiter);
    if(strcmp(temp, "")){
      args[i] = temp;
      i++;
    }
  }
  return args;
}

void redir_input(char ** arr, int i) {
  int fd;
  fd = open(arr[i + 1], O_RDONLY);
  dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  arr[i] = NULL;
  if (execvp(arr[0], arr) == -1){
    printf("Uh oh! %s\n", strerror(errno));
  }
  close(fd);
}

void redir_output(char ** arr, int i) {
  int fd;
  if(strcmp(arr[i], ">") == 0) {
    fd = open(arr[i + 1], O_CREAT | O_WRONLY, 0644);
  }
  else {
    fd = open(arr[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
  }
  if(fd == -1){
    printf("error: %s\n", strerror(errno));
  }
  dup(STDOUT_FILENO);
  dup2(fd, STDOUT_FILENO);
  arr[i] = NULL;
  if (execvp(arr[0], arr) == -1){
    printf("Uh oh!%s\n", strerror(errno));
  }
  close(fd);
}


char* strReplace(char* line, char target, char* newStr) {
  char* temp = calloc(sizeof(char), 1000);
  char* point = strchr(line, target);
  *point = 0;
  point++;
  strcat(temp, line);
  strcat(temp, newStr);
  strcat(temp, point);
  printf("%s\n", temp);

  int i = 0;
  while (temp[i++]);
  char* output = calloc(sizeof(char), i);
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
      printf("Uh oh!%s\n", strerror(errno));
    }
  }
  if (!strcmp(args[0], "exit")){
    exit(0);
  }
}

int pipey(char *args){
  char ** separated = parse_args(args, "|");
  char ** firstArg = parse_args(fixws(separated[0]), " ");
  char ** secondArg = parse_args(fixws(separated[1]), " ");

  char current[100];
  char base[100];
  int f = fork();
  if(f == 0){
    FILE *r = popen(firstArg[0], "r");
    while(fgets(base, 100, r)){
      base[sizeof(base) - 1] = '\0';
      strcat(current, base);
    }
    pclose(r);
    int check = execvp(firstArg[0], firstArg);
    if(check == -1){
      printf("Uh oh!%s\n", strerror(errno));
    }
  }
  else{
    int cpid = wait(NULL);
    FILE *w = popen(secondArg[0], "w");
    fprintf(w, "%s", current);
    pclose(w);
    int check = execvp(secondArg[0], secondArg);
    if(check == -1){
      printf("Uh oh!%s\n", strerror(errno));
    }
  }
  free(args);
  return 0;
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

  int i;
  for(i = 0; args[i] != NULL && (strcmp(args[i], ">") != 0 && strcmp(args[i], ">>") != 0
  && strcmp(args[i], "<") != 0 && strcmp(args[i], "|") != 0); i++);

  if(pid == 0){
    if(args[i] != NULL && (strstr(args[i], "|"))){
      pipey(line);
    }
    else if(args[i] != NULL && (strstr(args[i], ">") || (strstr(args[i], ">>")))) {
      redir_output(args, i);
    }
    else if(args[i] != NULL && (strstr(args[i], "<") || (strstr(args[i], "<<")))) {
      redir_input(args, i);
    }

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
  while(separated[i]){
    run_commands(separated[i]);
    i++;
  }
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
