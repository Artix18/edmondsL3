#include "graph.h"

int main()
{
	int i;
	int nbNoeuds, nbAretes, type;
	printf("Nombre de noeuds ? ");
	scanf("%d", &nbNoeuds);
	printf("Nombre d'arêtes ? ");
	scanf("%d", &nbAretes);
	printf("Quelle question résoudre ?\n");
	scanf("%d", &type);
	
	//Déclaration du graphe
	Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->nbNoeuds = nbNoeuds;
	graph->nbAretes = nbAretes;
	graph->aretes   = (Arc*) malloc(nbAretes * sizeof(Arc));
	graph->listeAdj = (Vecteur*)malloc(nbNoeuds * sizeof(Vecteur));
	init(graph->listeAdj,0);
	
	for(i = 0; i < nbAretes; i++)
	{
		int a,b;
		
		scanf("%d%d", &a,&b);
		
		graph->aretes[i].a=a;
		graph->aretes[i].b=b;
		graph->aretes[i].type=0;
		
		push_back(&graph->listeAdj[a],i);
		push_back(&graph->listeAdj[b],i);
	}

	switch(type)
	{
		case 0:
			diff_symetrique(graph);
		break;

		case 1:
		break;

		default:;
	}


	return 0;
}

