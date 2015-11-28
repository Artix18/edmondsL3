#include "graph.h"

int main()
{
	int i;
	int nbNoeuds, nbAretes, type;
	int idAr=0;
	printf("Quelle question résoudre ?\n");
	scanf("%d", &type);
	scanf("%d", &nbNoeuds);
	scanf("%d", &nbAretes);
	
	//Déclaration du graphe
	Graph *graph = nouveauGraphe(nbNoeuds, nbAretes);
	/*Graph *graph = (Graph*)malloc(sizeof(Graph));
	graph->nbNoeuds = nbNoeuds;
	graph->nbAretes = nbAretes;
	graph->idAretePrise = (int*)malloc(nbNoeuds * sizeof(int));
	graph->aretes   = (Arc*) malloc(nbAretes * sizeof(Arc));
	graph->listeAdj = (Vecteur*)malloc(nbNoeuds * sizeof(Vecteur));
	init(graph->listeAdj,0);
	
	for(i = 0; i < nbNoeuds; i++)
		graph->idAretePrise[i]=-1;*/
	
	for(i = 0; i < nbNoeuds; i++)
	{
		int nbAr;
		int j;
		scanf("%d", &nbAr);
		
		for(j = 0; j < nbAr; j++)
		{
			int b;
			scanf("%d", &b);
			
			if(b < i)
				continue;
			
			graph->aretes[idAr].a=i;
			graph->aretes[idAr].b=b;
			graph->aretes[idAr].type=0;

			push_back(&graph->listeAdj[i],idAr);
			push_back(&graph->listeAdj[b],idAr++);
		}
	}

	switch(type)
	{
		case 0:
			diff_symetrique(graph, 1);
		break;

		case 1:
			couplageMaximumBiparti(graph, 1);
		break;

		case 2:
			//TODO: tester la question 3 ici
		break;

		default:;
	}


	return 0;
}

