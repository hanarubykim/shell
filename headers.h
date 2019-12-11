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

int redir_input(char *line);

int redir_output(char *line);

int run_commands(char *line);
