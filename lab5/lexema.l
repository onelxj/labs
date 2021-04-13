%{
#include <stdio.h>
#include "bison.tab.h"
int line_no = 0;
%}

%%
[a-z]+		{printf("PROCEDURE_NAME\n");return(PROCEDURE_NAME);}
"("         	{printf("BRACKET_LEFT\n");return(BRACKET_LEFT);}
[a-z]+                  				{printf("PARAMETERS_VARIABLE\n");return(PARAMETERS_VARIABLE);}
[IVX]+                  				{printf("PARAMETERS_ROMAN\n");return(PARAMETERS_ROMAN);}
","                    			{printf("DELIMETER\n");return(DELIMETER);}
")"                    			{printf("BRACKET_RIGHT\n");return(BRACKET_RIGHT);}
";"                    			{printf(";\n");return(SEMICOLON);}

\n                    				line_no++;
%%

yywrap () {
  return (0);
}
