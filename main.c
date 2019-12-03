#include

int main(int argc, char **argv){
  char command[1000];
  if(argc <= 1){
    printf("Enter command: ");
    fgets(command, 1000, stdin);
  }else{
    strcpy(comand, argv[1]);
  }
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
