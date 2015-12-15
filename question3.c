#include "graph.h"

//il faut peut être faire gaffe si y'a une arete couplée qui sort de l'ensemble à fusionner ?
//attention, mon implémentation génère des graphes "à trous" (ie les noeuds seront numérotés par ex 1, 2, 15, 16, ...)
Graph* contracte(Graph* graph, Vecteur aContracter, int affiche)
{
	int i;
	int repres = get(&aContracter, 0);
	Graph* gRes = recopieGraphe(graph);

	for(i = 0; i < size(&aContracter); i++)
	{
		int noeud = get(&aContracter, i);
		int j;
		int sz = size(&gRes->listeAdj[noeud]);
		
		for(j = 0; j < sz; j++)
		{
			int idArete = get(&gRes->listeAdj[noeud], j);
			Arc *arete = &gRes->aretes[idArete];
			if(arete->a==noeud)
				arete->a=repres;
			if(arete->b==noeud)
				arete->b=repres;
			/*if(arete->a==repres && arete->b==repres)
			{
				sz--;
				swap(&gRes->listeAdj[noeud], j, sz);
				pop_back(&gRes->listeAdj[noeud]);
				j--;
			}*/
		}
	}

	if(affiche)
	{
		int noeud;
		
		printf("Graphe contracté :\n");
		printf("%d %d\n", gRes->nbNoeuds, gRes->nbAretes);
		
		for (noeud=0; noeud < gRes->nbNoeuds; noeud++)
		{
			int sz = size(&(gRes->listeAdj[noeud]));
			int idArete = get(&gRes->listeAdj[noeud], 0);
			Arc arete = gRes->aretes[idArete];
			if(sz == 0 || (arete.a != noeud && arete.b != noeud))
				continue;
			printf("noeud %d :\n", noeud);
			printf("%d ", sz);
			affiche_vecteur(&(gRes->listeAdj[noeud]));
		}
	}
	
	return gRes;
}

int contracte_bound (Graph *graph, Vecteur aContractern, int affiche) {
    int res = 4+affiche*3+graph->nbNoeuds*7;
    int noeud;
    for (noeud=0; noeud < graph->nbNoeuds; noeud++)
        res = res + affiche_vecteur_bound(&graph->listeAdj[noeud]);
    return res;
}
