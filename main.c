#include

int main(int argc, char **argv){
  run_shell();
  return 0;
}

void run_shell(){
  char *line;
  char **args;
  int status;

  line = read();
  args = parse(line);
  status = execute(args);
  free(line);
  free(args);
}

char read(){
  char *buffer = malloc(sizeof(char) * 1024);
  int pos = 0;
  int c;
  if(buffer == NULL){
    printf("ERROR");
  }
  while(){
    c = 
  }
}

char ** parse(char *line){
  char ** args = malloc(64 * sizeof(char));
  int i = 0;
  while(line != NULL){
    args[i] = strsep(&line, " ");
    i++;
  }
  args[i] = NULL;
  return args;
}
