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

int init_bound(Vecteur *vect, int n)
{
	return -1;
	//return 3*vect+4;
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

int push_back_bound(Vecteur *vect, int val)
{
	return -1;
	//return (vect->vapacite)*2+(vect->taille)*4+6;
}

int get(Vecteur *vect, int index)
{
	assert(index < vect->taille);
	return vect->tab[index];
}

int get_bound(Vecteur *vect, int index)
{
	return 2;
}
	
void set(Vecteur* vect, int index, int val)
{
	assert(index < vect->taille);
	vect->tab[index] = val;
}

int set_bound(Vecteur *vect, int index, int val)
{
	return 2;
}

int size(Vecteur *vect)
{
	return vect->taille;
}

int size_bound(Vecteur *vect)
{
	return 1;
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

int affiche_vecteur_bound(Vecteur *vect)
{
	4+2*(vect->taille);
}

int getAutreNoeud(Arc arc, int noeud)
{
	if(arc.a==noeud)
		return arc.b;
	return arc.a;
}

int getAutreNoeud_bound(Arc arc, int noeud)
{
	return 2;
}

Graph *nouveauGraphe(int nbNoeuds, int nbAretes)
{
	int i;
	Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->nbNoeuds = nbNoeuds;
	graph->nbAretes = nbAretes;
	graph->idAretePrise = (int*)malloc(nbNoeuds * sizeof(int));
	graph->aretes   = (Arc*) malloc(nbAretes * sizeof(Arc));
	graph->listeAdj = (Vecteur*)malloc(nbNoeuds * sizeof(Vecteur));
	init(graph->listeAdj,0);

	for(i = 0; i < nbNoeuds; i++)
		graph->idAretePrise[i]=-1;
	return graph;
}

int nouveauGraphe_bound(int nbNoeuds, int nbAretes)
{
	return -1;
	//return sizeof(Graph)+sizeof(int)+sizeof(Arc)+sizeof(Vecteur)+9+2*nbNoeuds;
}

Graph *recopieGraphe(Graph* g)
{
	int i;
	Graph *graph = nouveauGraphe(g->nbNoeuds, g->nbAretes);
	
	for(i = 0; i < g->nbNoeuds; i++)
	{
		graph->idAretePrise[i] = g->idAretePrise[i];
		graph->listeAdj[i]     = g->listeAdj[i];
	}
	for(i = 0; i < g->nbAretes; i++)
	{
		graph->aretes[i] = g->aretes[i];
		//graph->aretes[i].a = g->aretes[i].a;
		//graph->aretes[i].b = g->aretes[i].b;
		//graph->aretes[i].type = g->aretes[i].type;
	}
	
	return graph;
}

int recopieGraphe_bound(Graph *g)
{
	return -1;
	//return 3+nouveauGraphe_bound(g->nbNoeuds, g->nbAretes)+3*nbNoeuds+2*nbAretes;
}
