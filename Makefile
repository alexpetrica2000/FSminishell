build: list.o main.o
	gcc -Wall list.o file.h list.h main.o -o fsminishell
list.o:	list.c
	gcc -Wall -c  list.c
main.o: main.c
	gcc -Wall -c  main.c	
clean: 
	rm fsminishell
run: 
	./fsminishell
