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

char ** parse_args(char *line, char *delimiter);

char * fixws(char *arg);

void semicolon(char *line);

void redir_input(char ** arr, int i);

void redir_output(char ** arr, int i);

char* strReplace(char* line, char target, char* newStr);

void call_cd(char ** args);

int run_commands(char *line);
