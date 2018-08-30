#include "lex.yy.c"
#include <regex.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char id[999];
    int value;
} Variable;

Variable variables[999];
unsigned int n_var=0;
unsigned int n_line=0;


Variable* get_variable(char id[999]);
void attribute_variable(char id[999], char value[999]);
void add_variable(char id[999], char value[999]);
void print_variable(char id[999]);
void error_detected(Token* token);

int main(){
    Token* first_token; Token* sec_token;
    Token* third_token; Token* fourth_token; Token* fifth_token;

    init_lexical();

    n_line = 1;
    while(first_token = get_next_token()){
      switch (first_token->symbol) {
        case LET:
          sec_token = get_next_token();
          if(sec_token->symbol != ID){
            error_detected(sec_token);
          }
          third_token = get_next_token();
          if(third_token->symbol != EQUAL){
            error_detected(third_token);
          }
          fourth_token = get_next_token();
          if(fourth_token->symbol != INTEGER){
            error_detected(fourth_token);
          }
          fifth_token = get_next_token();
          if(fifth_token->symbol != ENDLINE && fifth_token){
            error_detected(fifth_token);
          }
          n_line++;
          attribute_variable(sec_token->value, fourth_token->value);
          break;
        case ADD:
          sec_token = get_next_token();
          if(sec_token->symbol != ID){
            error_detected(sec_token);
          }
          third_token = get_next_token();
          if(third_token->symbol !=  PLUS){
            error_detected(third_token);
          }
          fourth_token = get_next_token();
          if(fourth_token->symbol != INTEGER){
            error_detected(fourth_token);
          }
          fifth_token = get_next_token();
          if(fifth_token->symbol != ENDLINE && fifth_token){
            error_detected(fifth_token);
          }
          n_line++;
          add_variable(sec_token->value, fourth_token->value);
          break;
        case PRINT:
          sec_token = get_next_token();
          if(sec_token->symbol != ID){
            error_detected(sec_token);
          }
          third_token = get_next_token();
          if(third_token->symbol != ENDLINE && third_token){
            error_detected(third_token);
          }
          n_line++;
          print_variable(sec_token->value);
          break;
        default:
          error_detected(first_token);
      }
    }

    return 0;
}

Variable* get_variable(char id[999]){
    for(int i=0;i<n_var;++i){
        if(strcmp(variables[i].id, id) == 0){
            return &variables[i];
        }
    }
    strcpy(variables[n_var].id, id);
    variables[n_var].value = 0;
    return &variables[n_var++];
}

void attribute_variable(char id[999], char value[999]){
    Variable* var = get_variable(id);
    var->value = atoi(value);
}

void add_variable(char id[999], char value[999]){
    Variable* var = get_variable(id);
    var->value += atoi(value);
}
void print_variable(char id[999]){
    Variable* var = get_variable(id);
    printf("%d\n", var->value);
}

void error_detected(Token* token){
  fprintf(stderr, "Error detected in line %d: %s\n", n_line, token->value);
  exit(1);
}
