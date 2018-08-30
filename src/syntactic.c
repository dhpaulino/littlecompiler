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
      unsigned int n_lines=0;


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
          printf("OLD: %d SUM: %d\n", var->value, atoi(value));
          var->value += atoi(value);
      }
      void print_variable(char name[999]){
          Variable* var = get_variable(name);
          printf("%d\n", var->value);
      }
      int main(){
          Token* first_token; Token* sec_token;
          Token* third_token; Token* fourth_token; Token* fifth_token;
          int i=0;

          init_lexical();
          
          //TODO: print the line where the error occurred
          while(first_token = get_next_token()){
              // printf("%s\n", token);

              //Attribute
              if(first_token->symbol ==  LET){
                      sec_token = get_next_token();
                      if(sec_token->symbol == ID){
                          third_token = get_next_token();
                          if(third_token->symbol == EQUAL){
                              fourth_token = get_next_token();
                              if(fourth_token->symbol == INTEGER){
                                  fifth_token = get_next_token();
                                  if(fifth_token->symbol == ENDLINE || !fifth_token){
                                    n_lines++;
                                    attribute_variable(sec_token->value, fourth_token->value);
                                  }else{
                                    printf("Error at %d\n", n_lines);
                                  }
                              }else{
                                  // printf("erro %s\n", fourth_token);
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
              }else if(first_token->symbol ==  ADD){
                  sec_token = get_next_token();
                  if(sec_token->symbol == ID){
                      third_token = get_next_token();
                      if(third_token->symbol ==  PLUS){
                          fourth_token = get_next_token();
                          //ID or digit
                          if(fourth_token->symbol == INTEGER){
                            fifth_token = get_next_token();
                            if(fifth_token->symbol== ENDLINE || !fifth_token){
                              n_lines++;
                              add_variable(sec_token->value, fourth_token->value);
                            }else{
                              printf("Error at %d\n", n_lines);
                            }
                          }else{
                              // printf("Error A:  %s", fourth_token);
                              exit(1);
                          }
                      }else{
                          // printf("Error B: %s", third_token);
                          exit(1);
                      }
                  }else{
                      printf("Error C");
                      exit(1);

                  }
              }else if(first_token->symbol == PRINT){
                  sec_token = get_next_token();
                  if(sec_token->symbol == ID){
                    third_token = get_next_token();
                    if(third_token->symbol == ENDLINE || !third_token){
                      n_lines++;
                      print_variable(sec_token->value);
                    }else{
                      printf("Error at %d\n", n_lines);
                    }
                  }else{
                    printf("Error at %d\n", n_lines);
                  }
                }else{
                    printf("Error Print");
                    exit(1);
                }
              i++;
          printf("symbol: %d value: %s\n", first_token->symbol, first_token->value);
          }

          return 0;
      }
