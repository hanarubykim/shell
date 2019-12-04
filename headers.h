#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

//MAIN FUNCTION
int main(int argc, char **argv);

//RUNS THE SHELL
void run_shell();

//READS IN THE COMMAND LINE ARGUMENTS
char read();

//
char ** parse(char *line);
