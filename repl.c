#include <stdio.h>
#include <stdlib.h>

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32
#include <string.h>

static char input[2048];
/*Not original readline function*/
char* readline(char* prompt)
{
  fputs(prompt, stdout);
  fgets(input, 2048, stdin);
  char* copy = malloc(strlen(input)+1);
  strcpy(copy, input);
  copy[strlen(copy)-1]='\0';
  return copy;
}

void add_history(char* something){}
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv)
{
  /*Print version*/
  puts("Lisp version 0\n");
  puts("Print Control+C for exit\n");

  /*Never ending loop*/

  while(1)
  {
    /*Get input from user*/
    char* input = readline("lispy> ");
    /*Add input to history*/
    add_history(input);
    /*Printf echo*/
    printf("Echo: %s\n", input);
    /*Free retrieved input*/
    free(input);
  }

  return 0;
}
