%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int base = 1000, flag = 0, fg[40], cn = 0; 
char symbols[40][40], values[40][40], temp[20];
%}

keyword ("auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|if|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while")
identifier [a-zA-Z_][a-zA-Z0-9_]*
looping_construct {keyword}*\(.*\).
function {identifier}\(.*\);
int_constant [0-9]+
float_constant [0-9]+.[0-9]+
double_constant [0-9]+[.][0-9][.]+[0-9]+
character_constant \"[a-zA-Z0-9_]*\"
arithmetic_operator "+"|"-"|"*"|"/"|"%" 
arithmetic_assignment_operator [+\-*/%][+\-*/%]
logical_operator [&|!][&|]*
assignment_operator "="
bitwise_operator "^"|"&"|"|"|"<<"|">>"
special_character "["|"{"|"}"|"("|")"|","|";"|"]"
relational_operator <|<=|>|>=|=|!= 
%%

^#.* { printf("\t%s - preprocessor directive\n", yytext); }
^[\/\*][\/\*] {printf("\t%s - comment lines\n", yytext);}

{keyword} {
    int i = 0;
    printf("\t%s - keyword\n", yytext);
    if(strcmp(yytext, "int") == 0) flag = 2;
    else if(strcmp(yytext,"float") == 0) flag = 4;
    else if(strcmp(yytext,"double") == 0) flag = 8;
    else if(strcmp(yytext,"char") == 0) flag = 1;
}

{function} { 
    printf("\t%s - function call\n", yytext); }

{identifier} {
    printf("\t%s - identifier\n", yytext);
    strcpy(symbols[cn],yytext);
}

{int_constant} {
    printf("\t%s - integer constant\n", yytext); 
    strcpy(values[cn],yytext);
    fg[cn] = flag;
    cn++;
}

{float_constant} {
    printf("\t%s - float constant\n", yytext);
    strcpy(values[cn],yytext);
    fg[cn] = flag;
    cn++;
}

{double_constant} {
    printf("\t%s - double constant\n", yytext);
    strcpy(values[cn],yytext);
    fg[cn] = flag;
    cn++;
}

{character_constant} {
    printf("\t%s - char constant\n", yytext);
    strcpy(values[cn],yytext);
    fg[cn] = flag;
    cn++;
}

{arithmetic_operator} {
    printf("\t%s - arithmetic operator\n", yytext);
    strcpy(values[cn],yytext);
}

{arithmetic_assignment_operator} {
    printf("\t%s - arithmetic assignment operator\n", yytext);
    strcpy(values[cn],yytext);
}

{logical_operator} {
    printf("\t%s - logical operator\n", yytext);
    strcpy(values[cn],yytext);
}

{bitwise_operator} {
    printf("\t%s - bitwise operator\n", yytext);
    strcpy(values[cn],yytext);
}

{assignment_operator} {
    printf("\t%s - assignment operator\n", yytext);
    strcpy(values[cn],yytext);
}

{special_character} {
    printf("\t%s - special character\n", yytext);
    strcpy(values[cn],yytext);
}

{looping_construct} {
    printf("\t%s - keyword\n", yytext);
    strcpy(values[cn],yytext);
}

{relational_operator} {
    printf("\t%s - relational operator\n", yytext);
    strcpy(values[cn],yytext);
}
%%

int main()
{
    yyin = fopen("input.txt", "r");
    yylex();
    printf("**************************************************************************************************\n");
    printf("\t\tSymbol Table:\n\n\t\tType\tSymbol\tSize\tAddress\tValue\n");
    for (int i = 0; i < cn; i++)
    {
        switch(fg[i]){
            case 1: strcpy(temp, "char");break;
            case 2: strcpy(temp, "int");break;
            case 4: strcpy(temp, "float");break;
            case 8: strcpy(temp, "double");break;
        }
        printf("\t\t%s\t %s\t %d\t %d\t %s\n", temp, symbols[i], fg[i], base, values[i]);
        base += fg[i];
    }
    printf("**************************************************************************************************\n");
    return 0;
}