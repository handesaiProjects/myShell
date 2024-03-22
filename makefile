CC = gcc
FLAGS = -Wall -g

all: clean myShell
	./myShell

leak: clean myShell
	valgrind --leak-check=full --error-exitcode=1 ./myShell
	

myShell: myShell.o myFunction.o utilFunctions.o
	$(CC) $(FLAGS) -o myShell myShell.o myFunction.o utilFunctions.o

myShell.o: myShell.c myShell.h
	$(CC) $(FLAGS) -c myShell.c

myFunction.o: myFunction.c myFunction.h
	$(CC) $(FLAGS) -c myFunction.c

utilFunctions.o: utilFunctions.c utilFunctions.h
	$(CC) $(FLAGS) -c utilFunctions.c

clean:
	rm -f *.o *.out myShell 