all:
	gcc main.c graph.c graph.h diff_sym.c chemin_augm_biparti.c

clean :
	rm a.out *.gch *~
