#include "graph.h"

//il faut peut être faire gaffe si y'a une arete couplée qui sort de l'ensemble à fusionner ?
//attention, mon implémentation génère des graphes "à trous" (ie les noeuds seront numérotés par ex 1, 2, 15, 16, ...)
Graph* contracte(Graph* graph, Vecteur aContracter)
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
			if(arete->a==repres && arete->b==repres)
			{
				sz--;
				swap(&gRes->listeAdj[noeud], j, sz);
				pop_back(&gRes->listeAdj[noeud]);
				j--;
			}
		}
	}
	
	return gRes;
}
