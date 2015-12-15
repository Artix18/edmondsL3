all:
	g++ -g graph.c graph.h question5.c main.c 

clean :
	rm a.out *.gch *~
