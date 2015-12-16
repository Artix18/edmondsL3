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
	
	for(i = 0; i < nbNoeuds; i++)
	{
		int nbAr;
		int j;
		scanf("%d", &nbAr);
		
		for(j = 0; j < nbAr; j++)
		{
			int b;
			scanf("%d", &b);
			
			//printf("debug : %d\n", i);
			//graph->arcs[i].push_back(b);
			
			if(b < i)
				continue;
			
			graph->aretes[idAr].a=i;
			graph->aretes[idAr].b=b;
			graph->aretes[idAr].type=0;

			push_back(&graph->listeAdj[i],idAr);
			push_back(&graph->listeAdj[b],idAr++);
		}
	}

    int a;
	switch(type)
	{
		case 0:
			diff_symetrique(graph, 1);
		break;

		case 1:
			couplageMaximumBiparti(graph, 1); //renvoie une liste d'arêtes numérotées à partir de 0
		break;

		case 2:
		    printf("Nombre de noeuds de la liste à contracter :\n");
		    scanf("%d", &a);
		    printf("Entrez la liste des noeuds à contracter :\n");
		    Vecteur aContracter;
		    init(&aContracter, 0);
		    for(int i = 0; i < a; i++)
		    {
		        int b;
		        scanf("%d", &b);
		        push_back(&aContracter, b);
		    }
			contracte(graph, aContracter, 1);
		break;
		
		case 3:
		    printf("Nombre de noeuds dans la corolle :\n");
		    scanf("%d", &a);
		    printf("Entrez la liste des noeuds de la corolle :\n");
		    Vecteur corolle;
		    init(&corolle, 0);
		    for(int i = 0; i < a; i++)
		    {
		        int b;
		        scanf("%d", &b);
		        push_back(&corolle, b);
		    }
		    printf("Entrez le nombre de noeuds dans le chemin augmentant :\n");
		    int c;
		    scanf("%d", &c);
		    Vecteur chemin;
		    init(&chemin,0);
		    printf("Entrez le chemin augmentant dans l'ordre :\n");
		    for(int i = 0; i < c; i++)
		    {
		        int b;
		        scanf("%d", &b);
		        push_back(&chemin, b);
		    }
		    decompression(graph, corolle, chemin, get(&chemin, 0), 1);
		break;
		
		case 6:
		case 5:
		case 4:
		    couplageMax(graph,1);
		break;

		default:;
	}


	return 0;
}

