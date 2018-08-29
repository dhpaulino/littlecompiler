#include "lex.yy.c"
#include <regex.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[999];
    int value;
} Variable;

Variable variables[999];
unsigned int n_var=0;

regex_t DIGIT_REGEX;
regex_t ID_REGEX;
regex_t KEYWORD_REGEX;
regex_t EQUAL_REGEX;
regex_t PLUS_REGEX;


Variable* get_variable(char name[999]){
    for(int i=0;i<n_var;++i){
        if(strcmp(variables[i].name, name) == 0){
            return &variables[i];
        }
    }
    strcpy(variables[n_var].name, name);
    variables[n_var].value = 0;
    return &variables[n_var++];
}

void attribute_variable(char name[999], char value[999]){
    Variable* var = get_variable(name);
    var->value = atoi(value);
}

void add_variable(char name[999], char value[999]){
    Variable* var = get_variable(name);
    var->value += atoi(value);
}
void print_variable(char name[999]){
    Variable* var = get_variable(name);
    printf("%d\n", var->value);
}

void init_regex(){
    if(regcomp(&DIGIT_REGEX, "^[0-9]", 0) != 0){
        printf("out 1\n");
        exit(1);
    }
    if(regcomp(&ID_REGEX, "^[a-zA-Z][a-zA-Z0-9_]*", 0) != 0){
        exit(1);
    }
    if(regcomp(&KEYWORD_REGEX, "let|add|print", 0) != 0){
        exit(1);
    }
    if(regcomp(&EQUAL_REGEX, "^=", 0) != 0){
        exit(1);
    }
    if(regcomp(&PLUS_REGEX, "^+", 0) != 0){
        exit(1);
    }
}


int main(){
    Token* first_token; char* sec_token; char* third_token; char* fourth_token;
    int i=0;


    init_regex();
    init_lexical();

    //TODO: handle negative numbers
    //TODO: print the line where the error occurred
    //TODO: check if ID is not KEYWORD, EQUAL or PLUS
    while(first_token = get_next_token()){
    //     // printf("%s\n", token);
    //     printf("token %d:\n", i);
    //
    //     //Attribute
    //     if(strcmp(first_token, "let") == 0){
    //             sec_token = get_next_token();
    //             if(regexec(&ID_REGEX, sec_token, 0, NULL, 0) == 0){
    //                 third_token = get_next_token();
    //                 if(regexec(&EQUAL_REGEX, third_token, 0, NULL, 0) == 0){
    //                     fourth_token = get_next_token();
    //                     if(regexec(&DIGIT_REGEX, fourth_token, 0, NULL, 0) == 0){
    //                         printf("Ok\n");
    //                         attribute_variable(sec_token, fourth_token);
    //                     }else{
    //                         printf("erro %s\n", fourth_token);
    //                         printf("Error M");
    //                         exit(1);
    //                     }
    //                 }else{
    //                     printf("Error N");
    //                     exit(1);
    //                 }
    //             }else{
    //                 printf("Error Y");
    //                 exit(1);
    //             }
    //     }else if(strcmp(first_token, "add") == 0){
    //         sec_token = get_next_token();
    //         if(regexec(&ID_REGEX, sec_token, 0, NULL, 0) == 0){
    //             third_token = get_next_token();
    //             if(regexec(&PLUS_REGEX, third_token, 0, NULL, 0) == 0){
    //                 fourth_token = get_next_token();
    //                 //ID or digit
    //                 if(regexec(&DIGIT_REGEX, fourth_token, 0, NULL, 0) == 0){
    //                     printf("Ok\n");
    //                     attribute_variable(sec_token, fourth_token);
    //                 }else{
    //                     printf("Error A:  %s", fourth_token);
    //                     exit(1);
    //                 }
    //             }else{
    //                 printf("Error B: %s", third_token);
    //                 exit(1);
    //             }
    //         }else{
    //             printf("Error C");
    //             exit(1);
    //         }
    //
    //     }else if(strcmp(first_token, "print") == 0){
    //         sec_token = get_next_token();
    //         if(regexec(&ID_REGEX, sec_token, 0, NULL, 0) == 0){
    //             printf("ok\n");
    //             print_variable(sec_token);
    //         }else{
    //             printf("Error Print");
    //             exit(1);
    //         }
    //     }else{
    //         printf("%s\n", first_token);
    //         printf("Error D");
    //         exit(1);
    //     }
    //     i++;
    printf("symbol: %d value: %s\n", first_token->symbol, first_token->value);
    }

    return 0;
}
