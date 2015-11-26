#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define SZ_DEFAULT 5;
#define MAX_NB_NOEUDS 1000

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
void affiche_vecteur(Vecteur *vect);

//Représentation d'une arête. A noter qu'on aurait aussi pu recoder un "vector" et garder uniquement la destination, mais que cela aurait aussi necessiter de stocker l'indice de l'arête "inverse" lorsque l'on veut changer le type, ou juste un propre à l'arête.
typedef struct
{
	int a, b; //les deux extrémités 
	int type; //0 banal, 1 couplage

	/*Arc()
	{
	}
	
	Arc(int a, int b, int type) : a(a), b(b), type(type)
	{
	}*/
} Arc;

int getAutreNoeud(Arc arc, int noeud);

typedef struct
{
	int nbNoeuds,nbAretes;
	int *idAretePrise; //idAretePrise[noeud] = -1 si pas affecté, et l'id de l'arete sinon
	Arc *aretes;
	//int **adjMatrix; //on pourrait peut-être utiliser une matrice d'adj plutot...
	Vecteur *listeAdj;
	//int **listeAdj;
} Graph;

Vecteur diff_symetrique(Graph *, int);
Vecteur diff_symetrique2(Graph *graph, Vecteur *augm);
Vecteur couplageMaximumBiparti(Graph *graph, int affiche);

#endif

