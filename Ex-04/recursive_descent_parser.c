#include<stdio.h>
#include<stdlib.h>
void E();
void Eprime();
void T();
void Tprime();
void F();
char tok;
int pos = 0;

void parser(char c)
{
    if(tok == c) {
        tok = getchar();
    }
    else {
        printf("Error at position %d!\n", pos);
        exit(0);
    }
}

void E()
{
    printf("E()->");
    T();
    Eprime();
}

void Eprime()
{
    printf("E\'()->");
    if(tok == '+') {
        pos++;
        parser('+');
        T();
        Eprime();
    }
}

void T()
{
    printf("T()->");
    F();
    Tprime();
}

void Tprime()
{
    printf("T\'()->");
    if(tok == '*') {
        pos++;
        parser('*');
        F();
        Tprime();
    }
}

void F()
{
    printf("F()->");
    if(tok == '(') {
        pos++;
        parser('(');
        E();
        pos++;
        parser(')');
    }
    else if(tok == 'i') {
        pos++;
        parser('i');
        parser('d');
    }
    else {
        printf("Error at position %d!\n", pos);
        exit(0);
    }
}

void main()
{   
    printf("Enter string to be parsed : ");
    tok = getchar();
    E();
    printf("\nThe given string was parsed successfully!\n");
}