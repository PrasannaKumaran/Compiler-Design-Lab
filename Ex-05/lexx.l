%{
#include<stdio.h>
#include<stdlib.h>
#include "y.tab.h"
void yyerror(char *); 
extern int yylval;
%}

%%
[ \t]+ ;
[0-9]+ {yylval = atoi(yytext);
return INTEGER;}
[-+*/^] {return *yytext;}
"<<" {return LSHIFT;}
">>" {return RSHIFT;}
"&&" {return *yytext;}
"||" {return *yytext;}
"!" {return *yytext;}
"(" { return *yytext;}
")" {return *yytext;}
\n {return *yytext;}
. {char msg[25];
sprintf(msg, "%s<%s>","Invalid Character",yytext);
yyerror(msg);}
%%