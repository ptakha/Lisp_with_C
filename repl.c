#include <stdio.h>

/* Declare a buffer for user input of size 2048 */
static char input[2048];

int main(int argc, char** argv)
{
  /*Print version*/
  puts("Lisp version 0\n");
  puts("Print Control+C for exit\n");

  /*Never ending loop*/

  while(1)
  {
    /*Put 'lispy> ' to stdout */
    fputs("lispy> ", stdout);
    /*Get string(char*) from stdin of maximum size 2048 and put it to variable input */
    fgets(input, 2048, stdin);
    /*Printf echo*/
    printf("Echo: %s\n", input);
  }

  return 0;
}
