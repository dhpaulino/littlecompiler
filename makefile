FLEX=flex
CC=gcc
SRC=src
BIN=bin
all: compiler

compiler.yy.c: $(SRC)/compiler.lex
	$(FLEX)  -o $(SRC)/compiler.yy.c $(SRC)/compiler.lex

compiler: compiler.yy.c
	$(CC) -o $(BIN)/compiler $(SRC)/syntactic.c -lfl
	ln -s $(BIN)/compiler compiler

#------------------------------------------------------------------------------
clean :
	$(RM) compiler $(BIN)/* $(SRC)/compiler.yy.c
