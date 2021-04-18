%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"
void yyerror(char *);
extern int yylval;
int error_line = 1;
%}
string_array ([_a-zA-Z][_a-zA-Z0-9]*\[[0-9]*\])
num ([0-9\.]+)
string (\".*\")
character (\'.*\')
%%
("++"|"--") {return UNARY;}
("<"|">"|"!="|"=="|">="|"<=") { return RELATIONAL_OP;}
("+"|"-"|"*"|"/"|"%"|"<<"|">>"|"!"|"&&"|"||") { return OPERATOR;}
("+="|"-="|"*="|"/="|"=") {return ASSIGNMENT_OP;}
("int"|"float"|"char"|"double") { return DATATYPE; }
if {return IF;}
else {return ELSE;}
while {return WHILE;}
[_a-zA-Z_][a-zA-Z0-9]* {return IDENTIFIER;}
{string_array} { return STRING_ARR; }
{num} { return NUM; }
{string} {return STRING;}
{character} { return CHARACTER;}
[ \t]+ { }
[ \n] {error_line+=1;}
("\."|"("|")"|"{"|"}") {return *yytext;}
";" {return TERMINATOR;}
. {
  fprintf(stderr,"Unknown token found: <%s>\n", yytext);
}
%%