#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

char ** parse_args(char *line, char *delimiter);

int run_commands(char *line);

void semicolon(char *line);
