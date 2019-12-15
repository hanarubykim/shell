# shell

## Description and Features of Our Shell

Welcome to our shell baby ( ˘ ³˘)

Features our baby implements:
- Allows the use of semicolons
- Can handle extra whitespace between commands
- Forks and executes commands
- Handles redirection with < and >
- Able to cd and exit
- Singular pipes

## Features our baby unsuccessfully attempted to implement

All features should be working

- Program allows for extra white spaces before and after commands


## Bugs

- The pipes won’t work with “more” for specific commands (ex. Works for ls | more, but not ls -l | more)
- When using pipes, it will bring strerror, although it executes the command properly (ex. ls | wc)


## Functions

**char * fixws();**
- Inputs: char * arg
- Returns: Pointer to beginning of arg

- Removes leading and trailing whitespace on the string arg
- Terminating ‘/0’ is placed at a new location if necessary
- Returns a pointer to a string stripped of leading/trailing whitespace.


**char ** parse_args();**
- Inputs: char * line, char * delimiter
- Returns: Array of strings where each entry is a token separated by delimiter

- Parses command-line arguments so our shell can read in commands separated by a delimiter (ex. helper function for when command-line input has semicolons).

**void redir_input();**
- Inputs: char ** arr, int i
- Returns: N/A

- Redirection for `<`

**void redir_output();**
- Inputs: char ** arr, int i
- Returns: N/A

- Redirection for `>`

**char * strReplace();**
- Inputs: char* line, char target, char* newStr
- Returns: Pointer to beginning of modified line

- A helper function for `call_cd`. `line` is the targeted string, `target` is the character you want to change, and `newStr` is the string you want to replace it with. Does lots of concatenating strings so that you can `cd` into the right directory

**void call_cd();**
- Inputs: char ** args
- Returns: N/A

- Takes in args, an array of strings, and handles any `cd` calls

**void pipey();**
- Inputs: char * args
- Returns: N/A

- Handles pipes `|`

**int run_commands();**
- Inputs: char * line
- Returns: 0

- Takes in a string of commands and calls the proper functions to execute it

**void semicolon();**
- Inputs: char * line
- Returns: N/A

- Handles command-line inputs with multiple commands separated by semicolons.

**int main();**
- Inputs: N/A
- Returns: 0 if successful, -1 if unsuccessful

- Runs the shell.
