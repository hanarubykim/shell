#include

int main(int argc, char **argv){
  run_shell();
  return EXIT_SUCCESS;
}

void run_shell(void){
  char *line;
  char **args;
  int status;

  line = read();
  args = parse(line);
  status = execute(args);

    free(line);
    free(args);
  } while (status);
}
