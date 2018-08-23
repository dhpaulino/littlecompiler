FLEX=flex
CC=gcc
SRC=src
EXEC=exec
all: compiler

lex.yy.c: $(SRC)/compiler.lex
	$(FLEX) $(SRC)/compiler.lex

compiler: lex.yy.c
	$(CC) -o $(SRC)/lex.yy.c -O3 $(SRC)/lex.yy.c -lfl

#------------------------------------------------------------------------------
clean :
	$(RM) *.o
