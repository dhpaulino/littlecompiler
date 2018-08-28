%{
#include <stdio.h>
#include <string.h>

#define MAX_TOKEN 999


char tokens[MAX_TOKEN][999];
unsigned int n_tokens = 0;
unsigned int head_tokens = 0;


void add_token(char* c);
char* get_next_token();
%}

%x COMMENT

DIGIT		[0-9]
ID			[a-zA-Z][a-zA-Z0-9_]*
KEYWORD let|add|print
SYMBOL  "="|"+"
BLANK   [ \t\n]+

%%
{KEYWORD}           { add_token(yytext); }
{DIGIT}+	          { add_token(yytext); }
{ID}			          { add_token(yytext);}
{SYMBOL}            {add_token(yytext); }
%%



void add_token(char* c){
    strcpy(tokens[n_tokens], c);
    n_tokens++;
}
char* get_next_token(){
    if(head_tokens >= 0 && head_tokens < n_tokens){
        return tokens[head_tokens++];
    }
    return NULL;
}
int main(){

    yylex();
    char* token;
    int i=0;
    while(token = get_next_token()){
        printf("token %d:\n", i);
        printf("%s\n", token);
        i++;
    }
    return 0;
}
