#include "graph.h"

Vecteur diff_symetrique(Graph *graph, int affiche)
{
	int i;
	int nbAretesCouplage, nbAretesChemin;
	Vecteur solution;
	init(&solution, 0);

	printf("Combien d'arêtes dans le couplage ?\n");
	scanf("%d", &nbAretesCouplage);
	printf("Liste des arêtes :\n");
	for(i = 0; i < nbAretesCouplage; i++)
	{
		int id;
		scanf("%d", &id);
		
		graph->aretes[id].type = 1;
	}
	
	printf("Combien d'arêtes dans le chemin augmentant ?\n");
	scanf("%d", &nbAretesChemin);
	printf("Liste des arêtes :\n");
	for(i = 0; i < nbAretesChemin; i++)
	{
		int id;
		scanf("%d", &id);
		
		if(graph->aretes[id].type == 0)
			push_back(&solution, id);
	}

	if(affiche)
	{
		printf("Ou exclusif :\n");
		affiche_vecteur(&solution);
	}
	return solution;
}

Vecteur diff_symetrique2(Graph *graph, Vecteur *augm)
{
	int i;
	Vecteur solution;
	int nbAretesChemin = size(augm);
	init(&solution, 0);

	for(i = 0; i < nbAretesChemin; i++)
	{
		int id = get(augm, i);
		if(graph->aretes[id].type == 0)
			push_back(&solution, id);
	}

	return solution;
}

int diff_symetrique2_bound(Graph *graph, Vecteur *augm) {
	return size(augm)*size(augm)+5;
}
