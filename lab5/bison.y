%{#include<stdio.h>%}

%token PROCEDURE_NAME
%token BRACKET_LEFT
%token PARAMETERS_ROMAN
%token PARAMETERS_VARIABLE
%token DELIMETER
%token BRACKET_RIGHT
%token SEMICOLON

%%

calls : call | calls call SEMICOLON 
call : PROCEDURE_NAME BRACKET_LEFT parameters BRACKET_RIGHT
parameters : parameter | parameters DELIMETER parameter
parameter : PARAMETERS_ROMAN | PARAMETERS_VARIABLE
%%

extern int line_no;
extern char *yytext;

int yyerror(s)
char *s;
{
  fprintf(stderr, "%s: at or before '%s', line %d\n", s, yytext, line_no);
}

main (void) {
    setlocale(0,"");
    if(yyparse()){
      printf("error"); 
    }
    else {
      printf("good"); 
    }
    return;
}
