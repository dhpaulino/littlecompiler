%{
#include <stdio.h>
#include <string.h>

#define SYMBOLS_NUM 30
int unknown_count = 0;
int convert(char* c);
unsigned int symbol_count[SYMBOLS_NUM] = {0};
const char* symbols[SYMBOLS_NUM] = { "&", "(", ")", "*", "+", ",", "-", "/", ":=",       \
                                     ";", "<", "<=", "<>", "=", ">", ">=", "|",          \
                                     "COMENTARIO", "do", "else", "end", "function", "if",\
                                     "IDENTIFICADOR", "in", "INTEIRO", "let", "then",    \
                                     "var", "while"};
%}

%x COMMENT

DIGIT		[0-9]
ID			[a-zA-Z][a-zA-Z0-9_]*
KEYWORD let|add|print
SYMBOL  ":="|";"|","|"("|")"|"+"|"-"|"*"|"/"|"="|"<>"|">"|"<"|">="|"<="|"&"|"|"
BLANK   [ \t\n]+

%%
{KEYWORD}           { symbol_count[convert(yytext)] += 1; }
{DIGIT}+	          { symbol_count[convert("INTEIRO")] += 1; }
{ID}			          { symbol_count[convert("IDENTIFICADOR")] += 1; }
{SYMBOL}            { symbol_count[convert(yytext)] += 1; }
%%
