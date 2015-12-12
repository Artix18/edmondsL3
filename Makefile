all:
	gcc main.c graph.c graph.h diff_sym.c chemin_augm_biparti.c question3.c question4.c question5.c

clean :
	rm a.out *.gch *~
