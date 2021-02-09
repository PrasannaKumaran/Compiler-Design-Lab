#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

struct symbolTable{
    char identifier_name[30];
    char type[50];
    int no_of_bytes;
    int address;
    char value[30];
}st[100];
int row = 0; 

int isSymbol(FILE* output_file, char* line, int index){
    int symbol_state = 0;
    if((line[index] == '+') || (line[index] == '-') || (line[index] == '*') || 
        (line[index] == '/') || (line[index]== '%')){
        if((line[index + 1]) == '='){
            fprintf(output_file, "\n%c%c - Arithmetic assignment operator", line[index], line[index + 1]);
            symbol_state = 2;
        }
        else if((line[index + 1] == '+') || (line[index + 1] == '-')){
            fprintf(output_file, "\n%c%c - Unary operator", line[index], line[index + 1]);
            symbol_state = 2;
        }
        else{
            fprintf(output_file, "\n%c - Arithmetic operator", line[index]);
            symbol_state = 1;
        }
    }  
    if((line[index] == '&') || (line[index] == '|') || (line[index] == '!') ||
            (line[index] == '<') || (line[index] == '^') || (line[index] == '=') ||  
            (line[index]== '>')){
                if(line[index + 1] == '='){
                    fprintf(output_file, "\n%c%c - Relational operator", line[index], line[index + 1]);
                    symbol_state = 2;
                }
                else if((line[index + 1] == '&') || (line[index + 1] == '|')){
                    fprintf(output_file, "\n%c%c - Logical operator", line[index], line[index + 1]);
                    symbol_state = 2;
                }
                else if((line[index + 1] == '<') || (line[index + 1] == '>')){
                    fprintf(output_file, "\n%c%c - Bitwise operator", line[index], line[index + 1]);
                    symbol_state = 2;
                }
                else if(line[index] == '='){
                    fprintf(output_file, "\n%c - Assignment operator", line[index]);
                    symbol_state = 1;
                }
                else if(line[index] == '!'){
                    symbol_state = 1;
                    fprintf(output_file, "\n%c - Logical operator", line[index]);
                }
                else if((line[index] == '<') || (line[index] == '>')){
                    symbol_state = 1;                
                    fprintf(output_file, "\n%c - Relational operator", line[index]);
                }
                else if((line[index] == '^') || (line[index] == '&') || (line[index] == '|')){
                    symbol_state = 1;
                    fprintf(output_file, "\n%c - Bitwise operator", line[index]); 
                }
                else if((line[index] == ' ') || (line[index] == '\n')){
                    symbol_state = 1;
                }
            }
    if((line[index] == ';') || (line[index] == ',') ||
        (line[index] == '(') || (line[index] == '[') || (line[index] == '{') ||
        (line[index] == ')') || (line[index] == ']') || (line[index] == '}') ||
        (line[index] == ' ')){
        symbol_state = 1;
        if (line[index] != ' ')
            fprintf(output_file, "\n%c - Special character", line[index]);
    }               
    return symbol_state;
}

char* updateTable(FILE* output_file, char* line, const char* keyword){
    static int address = 1000;
    char type[50];
    int no_of_bytes;
    char *return_data_type = (char*)malloc(100);
    if(strstr(line, "unsigned long int")){
        strcpy(type, "unsigned long int");
        no_of_bytes = 4;
    }
    if(strstr(line, "unsigned short int")){
        strcpy(type, "unsigned short int");
        no_of_bytes = 1;
    }
    if(strstr(line, "signed short int")){
        strcpy(type, "signed short int");
        no_of_bytes = 2;
    }
    if(strstr(line, "signed long int")){
        strcpy(type, "signed long int" );
        no_of_bytes = 4;
    }
    if(strstr(line, "unsigned int")){
        strcpy(type, "unsigned int");
        no_of_bytes = 2;
    }
    if(strstr(line, "signed int")){
        strcpy(type, "signed int");
        no_of_bytes = 2;
    }
    if(strstr(line, "long int")){
            strcpy(type, "long int" );
            no_of_bytes = 4;
    }
    if(strstr(line, "short int")){
            strcpy(type, "short int");
            no_of_bytes = 1;
    }
    if(strstr(keyword, "float")){
        strcpy(type, "float");
        no_of_bytes = 4;
    }
    if(strstr(line, "double")){
        if(strstr(line, "long double")){
            strcpy(type, "long double");
            no_of_bytes = 10;
        }
        else {
            strcpy(type, "double");
            no_of_bytes = 8;   
        }
    }
    if(strstr(keyword, "char")){
        if(strstr(line, "unsigned")){
            strcpy(type, "unsigned char");
            no_of_bytes = 1;
            }
        else if(strstr(line, "signed")){
            strcpy(type, "signed char");
            no_of_bytes = 1;
            }
        else{
            strcpy(type, "char");
            no_of_bytes = 1;
        }
    }
    if(strstr(keyword, "void")){
        strcpy(type, "void");
        no_of_bytes = 0;
        address += -1;
    }
    int j = 0;
    char identi_[20];
    int key = -1;
    for(int i = 0; i < strlen(line); i++){
        if(isSymbol(output_file, line, i) > 0){
            if(line[i] == '=')
                key = 0;
            else if((line[i] == ',') || (line[i] == ';'))
                key = 1;
            else if((line[i] == '.'))
                continue;
            if(key == 0){
                strcpy(st[row].identifier_name, identi_);
                fprintf(output_file, "\n%s - Identifier", identi_);
                st[row].address = address + no_of_bytes;
                address = st[row].address;
                key = 1;
            }
            else if (key == 1){
                strcpy(st[row].value, identi_);
                char write_var[40];
                strcpy(write_var, identi_);
                if(strstr(type, "int"))
                    strcat(write_var, " - Integer constant");
                if(strstr(type, "float"))
                    strcat(write_var, " - Float constant");
                if(strstr(type, "double"))
                    strcat(write_var, " - Double constant");
                if(strstr(type, "char"))
                    strcat(write_var, " - Character constant");
                fprintf(output_file, "\n%s", write_var);
                strcpy(st[row].type, type);
                st[row].no_of_bytes = no_of_bytes;
                key = 0;
                row++;
            }
            memset(identi_, 0, strlen(identi_));
            j = 0;         
        }
        else
            identi_[j++] = line[i];
    }
    strcpy(return_data_type, type);
    return return_data_type;
}

int isFunctionCall(FILE* output_file, char* word){

    const char* functionCalls[] = {"printf", "scanf", "getch", "clrscr", "main"};
    for(int i = 0; i < sizeof(functionCalls)/sizeof(const char*); i++){
        if(strstr(word, functionCalls[i]))
            return 1;
    }
    return 0;
}

int isKeyWord(FILE* output_file, char* word){
    const char* keywords[] = {
                            "auto ","break","case","char","const",
                            "continue","default","double","long","else",
                            "enum","extern","float","for","goto",
                            "if","int","do","register","return",
                            "short","signed","sizeof","static","struct",
                            "switch","typedef","union","unsigned","void",
                            "volatile","while"
                            };
    for(int i = 0; i < sizeof(keywords)/sizeof(const char*); i++){
        if(strstr(word, keywords[i]) > 0)
            return 1;
    }
    return 0;
}

void printSymboltable(){
    for(int i =0; i < row; i++){
        printf("NAME : %-10s\tTYPE : %-15s\tBYTES: %-3d\tADDRESS: %-10d\tVALUE: %-15s\n", 
        st[i].identifier_name, 
        st[i].type, st[i].no_of_bytes, st[i].address
        ,st[i].value);
    }
}

void main(){
    FILE *input_file;
    FILE *output_file;
    input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");
    char * line = NULL;
    size_t len = 0;
    ssize_t read; 
    int j = 0;
    char cur_word[50];
    int open_comment = 0;
    int Fcal;                    
    while((read = getline(&line, &len, input_file) != -1)){
        int str_length = strlen(line);
        char working_line[str_length + 20];
        int funCall_p = 0;
        int key_p = 0;
        if (line[0] == '#'){
            fprintf(output_file, "\n%s - preprocessor directive", line);
            continue;
        }
        if((line[0] == '/') && ((line[1] == '/') || (line[1] == '*'))){
            fprintf(output_file, "\n%s - comment line", line);
            if (line[1] == '*')
                open_comment += 1;
            if((line[str_length - 2] == '/') && (line[str_length - 3] == '*'))
                 open_comment -= 1;
            continue;
        }
        if((line[str_length - 2] == '/') && (line[str_length - 3] == '*')){
            fprintf(output_file, "\n%s - comment line", line);
            open_comment -= 1;
            continue;
        }
        if(open_comment > 0){
            fprintf(output_file, "\n%s - comment line", line);
            continue;
        }
        if(strstr(line, "else")){
            fprintf(output_file, "\n%s - keyword", line);
            memset(cur_word, 0, strlen(cur_word));
            continue;
        }
        for(int i = 0; i < str_length;){
            int symbol_state = isSymbol(output_file, line, i);
            if (symbol_state == 0)
                cur_word[j++] = line[i++];
            else{
                j = 0;
                if(line[i] == '('){
                    int funcCall = isFunctionCall(output_file, cur_word);
                    Fcal = funcCall;
                    if(funcCall == 1){
                        fprintf(output_file, "\n%s - Function call", line);
                        memset(cur_word, 0, strlen(cur_word));
                        break;
                    }
                    else{
                        if((strstr(line, "if") > 0) || (strstr(line, "while") > 0)){
                            fprintf(output_file, "\n%s - Keyword", cur_word);
                            memset(cur_word, 0, strlen(cur_word));
                        }
                        else{
                            fprintf(output_file, "\n%s - Custom function call", cur_word);}
                            memset(cur_word, 0, strlen(cur_word));
                    }
                    int count_ = 0;
                    for(int k = i; k < str_length; k++){
                        if (line[k] == '"')
                            ++count_;
                        if (count_ == 2){
                            i += k;
                            break;
                        }
                    }
                }                       
                int keyWord = isKeyWord(output_file, cur_word);
                if(keyWord == 1){
                    if((strcmp(cur_word, "int") == 0) || (strstr(cur_word, "float") > 0) ||
                        (strstr(cur_word, "char") > 0) || (strstr(cur_word, "void") > 0)
                        || (strstr(cur_word, "double") > 0) || (strstr(cur_word, "long") > 0) ||
                        (strstr(cur_word, "unsigned") > 0) || (strstr(cur_word, "signed") > 0) ||
                        (strstr(cur_word, "short") > 0)){
                        memset(cur_word, 0, strlen(cur_word));
                        char * final_data_type = updateTable(output_file, line, cur_word);
                        fprintf(output_file, "\n%s - keyword", final_data_type);
                        break;
                    }
                    else
                    {
                        fprintf(output_file, "\n%s - keyword", cur_word);
                        memset(cur_word, 0, strlen(cur_word));
                        break;
                    }
                }
                else if((Fcal != 1) && (keyWord == 0))
                {
                    if(cur_word[0] != '\0'){
                        fprintf(output_file, "\n%s - keyword", cur_word);
                        memset(cur_word, 0, strlen(cur_word));   
                    }
                }
                i += symbol_state;
            }  
        }
    }
    if(open_comment != 0)
        printf("Open comment lines. WARNING!.\n");
    printSymboltable();
}