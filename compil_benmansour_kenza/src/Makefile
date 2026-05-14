EXEC = projet

SRC = main.c parser_regex.c ast.c nfa.c dfa.c minimize.c graphviz.c generator.c utils.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

run:
	./$(EXEC) test.txt

graphs:
	dot -Tpng nfa.dot -o nfa.png
	dot -Tpng dfa.dot -o dfa.png
	dot -Tpng min_dfa.dot -o min_dfa.png

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(EXEC) *.dSYM *.dot *.png generated_lexer.c lexer_generated

.PHONY: all clean run graphs