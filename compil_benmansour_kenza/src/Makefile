EXEC = projet  
OBJ = main.o dfa.o nfa.o ast.o graphviz.o

all: $(EXEC)

$(EXEC): $(OBJ)
	gcc -o $(EXEC) $(OBJ)

.PHONY : all clean

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o projet