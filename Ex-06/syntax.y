%{
    #include<stdio.h>
    #include<stdlib.h>
    #include<math.h>
    #include "y.tab.h"
    extern int error_line;
    int yylex(void);
    void yyerror();
    int flag=0;
%}
%token NUM IDENTIFIER  STRING_ARR STRING CHARACTER UNARY DATATYPE RELATIONAL_OP OPERATOR ASSIGNMENT_OP IF ELSE WHILE TERMINATOR

%%
    program:     statement program 
               | statement 
               ;
    statement:   declare TERMINATOR
               | assignment TERMINATOR
               | expression TERMINATOR
               | conditional 
               | looping 
               ;
    declare:     DATATYPE IDENTIFIER
               | DATATYPE STRING_ARR
               | DATATYPE STRING_ARR ASSIGNMENT_OP expression
               | DATATYPE IDENTIFIER ASSIGNMENT_OP expression
    assignment:  IDENTIFIER ASSIGNMENT_OP expression
    conditional: IF expression statement ELSE statement
               | IF expression statement ELSE '{' program '}'
               | IF expression '{' program '}' ELSE statement
               | IF expression '{' program '}' ELSE '{' program '}'
               | IF expression statement
               | IF expression '{' program '}'
    looping:     WHILE '(' expression ')' '{' program '}'
               | WHILE '(' assignment ')' '{' program '}'
    expression:  expression OPERATOR expression
               | expression RELATIONAL_OP expression
               | '(' expression ')'
               | IDENTIFIER UNARY
               | IDENTIFIER | NUM | NUM'.'NUM | STRING | CHARACTER
               ;
     
%%


void yyerror(){
    fprintf(stderr, "Invalid syntax at Line No : ");
    printf("%d\n",error_line);
    flag = 1;
    return;
}
int yywrap(){
    return 1;
}
int main()
{
    yyparse();
    if(!flag){
        printf("Given input is Valid!.\n");
    }
    return 0;
}