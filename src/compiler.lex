%{
#include <stdio.h>
#include <string.h>

#define MAX_TOKEN 999
#define MAX_SIZE_TOKEN 999
typedef enum{
    INTEGER,
    ID,
    LET,
    ADD,
    PRINT,
    EQUAL,
    PLUS,
    ENDLINE
} Symbol;
typedef struct{
    Symbol symbol;
    char value[MAX_SIZE_TOKEN];
} Token;

Token tokens[MAX_TOKEN];
unsigned int n_tokens = 0;
unsigned int head_tokens = 0;


void add_token(Symbol symbol, char* value);
void add_let(char *c);
void add_print(char *c);
void add_add(char *c);
void add_integer(char *c);
void add_id(char *c);
void add_equal(char *c);
void add_plus(char *c);
void add_endline(char *c);
Token* get_next_token();
%}

%x COMMENT

DIGIT		[0-9]
SIGN    [+-]
ID			[a-zA-Z][a-zA-Z0-9_]*
LET let
PRINT print
ADD add
EQUAL "="
PLUS "+"
BLANK   [ \t]+
ENDLINE [\n]
%%
{LET}           { add_let(yytext); }
{PRINT}           { add_print(yytext); }
{ADD}           { add_add(yytext); }
{SIGN}*{DIGIT}+	          { add_integer(yytext); }
{ID}			          { add_id(yytext);}
{EQUAL}            {add_equal(yytext); }
{PLUS}            {add_plus(yytext); }
{ENDLINE} {add_endline(yytext);}

%%



void add_token(Symbol symbol, char* value){
    tokens[n_tokens].symbol = symbol;
    strcpy(tokens[n_tokens].value, value);
    n_tokens++;
}
void add_let(char *c){
    add_token(LET, c);
}
void add_print(char *c){
    add_token(PRINT, c);
}
void add_add(char *c){
    add_token(ADD, c);
}
void add_integer(char *c){
    add_token(INTEGER, c);
}
void add_id(char *c){
    add_token(ID, c);
}
void add_equal(char *c){
    add_token(EQUAL, c);
}
void add_plus(char *c){
    add_token(PLUS, c);
}
void add_endline(char *c){
    add_token(ENDLINE, c);
}

Token* get_next_token(){
    if(head_tokens >= 0 && head_tokens < n_tokens){
        return &tokens[head_tokens++];
    }
    return NULL;
}

void init_lexical(){
    yylex();
}
