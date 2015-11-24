#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define SZ_DEFAULT 5;

//Bon on va quand même implémenter un vecteur
typedef struct
{
	int capacite;
	int taille;
	int *tab;
} Vecteur;

void init(Vecteur*, int);
void push_back(Vecteur* vect, int val);
int get(Vecteur *vect, int index);
void set(Vecteur* vect, int index, int val);
int size(Vecteur *vect);

//Représentation d'une arête. A noter qu'on aurait aussi pu recoder un "vector" et garder uniquement la destination, mais que cela aurait aussi necessiter de stocker l'indice de l'arête "inverse" lorsque l'on veut changer le type, ou juste un propre à l'arête.
typedef struct
{
	int a, b; //les deux extrémités 
	int type;

	/*Arc()
	{
	}
	
	Arc(int a, int b, int type) : a(a), b(b), type(type)
	{
	}*/
} Arc;

typedef struct
{
	int nbNoeuds,nbAretes;
	Arc *aretes;
	Vecteur *listeAdj;
	//int **listeAdj;
} Graph;

void diff_symetrique(Graph *);

#endif

