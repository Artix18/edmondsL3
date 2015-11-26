#include "graph.h"

void init(Vecteur* vect, int n)
{
	int i;

	vect->taille = n;
	vect->capacite  = 2*n;
	vect->tab = (int*)malloc(vect->capacite*sizeof(int));

	for(i = 0; i < vect->taille; i++)
		vect->tab[i]=0;
}

void push_back(Vecteur* vect, int val)
{
	if(vect->taille*4 >= 3*vect->capacite)
	{
		int *tmp = (int*)malloc(vect->capacite*sizeof(int));
		int i;

		for(i = 0; i < vect->taille; i++)
			tmp[i]=vect->tab[i];

		free(vect->tab);
		vect->capacite <<= 1;
		vect->tab = (int*)malloc(vect->capacite*sizeof(int));
		for(i = 0; i < vect->taille; i++)
			vect->tab[i]=tmp[i];
		free(tmp);
	}

	vect->taille++;
	vect->tab[vect->taille-1]=val;
}

int get(Vecteur *vect, int index)
{
	assert(index < vect->taille);
	return vect->tab[index];
}
	
void set(Vecteur* vect, int index, int val)
{
	assert(index < vect->taille);
	vect->tab[index] = val;
}

int size(Vecteur *vect)
{
	return vect->taille;
}

void affiche_vecteur(Vecteur *vect)
{
	int i;
	if(vect->taille==0)
		return;
	printf("%d", vect->tab[0]);
	for(i = 1; i < vect->taille; i++)
		printf(" %d", vect->tab[i]);
	putchar('\n');
}

int getAutreNoeud(Arc arc, int noeud)
{
	if(arc.a==noeud)
		return arc.b;
	return arc.a;
}

