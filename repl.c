#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>


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
