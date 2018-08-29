#include "lex.yy.c"
#include <regex.h>
#include <string.h>

regex_t DIGIT_REGEX;
regex_t ID_REGEX;
regex_t KEYWORD_REGEX;
regex_t EQUAL_REGEX;
regex_t PLUS_REGEX;

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

    init_regex();
    init_lexical();
    char* token;
    int i=0;
    //TODO: create table of variables
    //TODO: check if ID is not KEYWORD, EQUAL or PLUS
    while(token = get_next_token()){
        // printf("%s\n", token);
        printf("token %d:\n", i);

        if(strcmp(token, "let") == 0){
                token = get_next_token();
                if(regexec(&ID_REGEX, token, 0, NULL, 0) == 0){
                    token = get_next_token();
                    if(regexec(&EQUAL_REGEX, token, 0, NULL, 0) == 0){
                        token = get_next_token();
                        if(regexec(&DIGIT_REGEX, token, 0, NULL, 0) == 0){
                            printf("Ok\n");
                        }else{
                            printf("erro %s\n", token);
                            printf("Error M");
                            exit(1);
                        }
                    }else{
                        printf("Error N");
                        exit(1);
                    }
                }else{
                    printf("Error Y");
                    exit(1);
                }
        }else if(strcmp(token, "add") == 0){
            token = get_next_token();
            if(regexec(&ID_REGEX, token, 0, NULL, 0) == 0){
                token = get_next_token();
                if(regexec(&PLUS_REGEX, token, 0, NULL, 0) == 0){
                    token = get_next_token();
                    //ID or digit
                    if(regexec(&ID_REGEX, token, 0, NULL, 0) == 0 || regexec(&DIGIT_REGEX, token, 0, NULL, 0) == 0){
                        printf("Ok\n");
                    }else{
                        printf("Error A:  %s", token);
                        exit(1);
                    }
                }else{
                    printf("Error B: %s", token);
                    exit(1);
                }
            }else{
                printf("Error C");
                exit(1);
            }

        }else if(strcmp(token, "print") == 0){
            token = get_next_token();
            if(regexec(&ID_REGEX, token, 0, NULL, 0) == 0){
                printf("ok\n");
            }else{
                printf("Error Print");
                exit(1);
            }
        }else{
            printf("%s\n", token);
            printf("Error D");
            exit(1);
        }
        i++;
    }

    return 0;
}
