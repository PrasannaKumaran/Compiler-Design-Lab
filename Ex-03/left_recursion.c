#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
    FILE *input_file, *output_file;
    input_file = fopen("input.txt", "r");
    output_file = fopen("output.txt", "w");
    char * line = NULL;
    size_t len = 0;
    ssize_t read; 
    char left_production[10];
    char right_production[10];
    int l, r, i, k, b;
    char nonTerminal;
    char split_[10][10];
    char buffer[10];
    while((read = getline(&line, &len, input_file) != -1)){
        int j = 0;
        for(l = 0; line[l] != '>'; l++){
            left_production[j++] = line[l];
        }
        left_production[j] = line[l];
        for(r = j + 1, i = 0; r < strlen(line); r++, i++)
            right_production[i] = line[r];
        left_production[j + 1] = '\0';
        right_production[i] = '\0';
        char *tempRight = malloc(sizeof(char) * strlen(right_production));
        strcpy(tempRight, right_production);
        nonTerminal = left_production[0];
        char * token;
        token = strtok(right_production, "|");
        int s = 0;
        while(token != NULL){
            strcpy(split_[s++], token);
            token = strtok(NULL, "|");
        }
        int index = -1;
        for(int i = 0; i < s; i++){
            if(split_[i][0] == nonTerminal){
                index = i;
                break;
            }
        }
        if(index == -1){
            printf("The production %s%s is non recursive\n",left_production, tempRight);
            fprintf(output_file, "\n%s%s", left_production, tempRight);
            continue;
        }
        else{
            for(int i = 0; i < s; i++){
                if(nonTerminal != split_[i][0]){
                    split_[i][strcspn(split_[i], "\n")] = 0;
                    fprintf(output_file, "\n%c->%s%c'", nonTerminal, split_[i], nonTerminal);
                }
                else{
                    for(k = 1, b = 0; k < strlen(split_[i]); k++, b++)
                        buffer[b] = split_[i][k];
                    buffer[strcspn(buffer, "\n")] = 0;
                    fprintf(output_file, "\n%c'->%s%c'|e", nonTerminal, buffer, nonTerminal);
                }
            }
        }
        memset(left_production, 0, strlen(left_production));
        memset(right_production, 0, strlen(right_production));
        memset(split_, 0, sizeof(split_[0][0]) * 10 * 10);
    }
}