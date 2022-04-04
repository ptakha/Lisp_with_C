#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

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
  /*Create new parsers*/
  mpc_parser_t* Int = mpc_new("int");
  mpc_parser_t* Float = mpc_new("float");
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expression = mpc_new("expression");
  mpc_parser_t* Polish_Notation = mpc_new("pn");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                           \
     int:    /-?[0-9]+/;                                        \
     float:  /-?[0-9]+\\.[0-9]+/;                               \
     number: <int> | <float>;                                   \
     operator: '+' | '-' | '*' | '/' | '%';                     \
     expression: <number> | '(' <operator>  <expression>+ ')';  \
     pn: /^/<operator> <expression>+/$/;                        \
    ",
    Int, Float, Number, Operator, Expression, Polish_Notation);

  /*Print version*/
  puts("Lisp version > 0\n");
  puts("Print Control+C for exit\n");

  /*Never ending loop*/

  while(1)
  {
    /*Get input from user*/
    char* input = readline("lispy> ");
    /*Add input to history*/
    add_history(input);
    /*Use polish notation*/
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Polish_Notation, &r))
    {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    }
    else
    {
      mpc_err_print(r.output);
      mpc_err_delete(r.output);
    }
    /*Free retrieved input*/
    free(input);
  }

  mpc_cleanup(6, Int, Float, Number, Operator, Expression, Polish_Notation);

  return 0;
}
