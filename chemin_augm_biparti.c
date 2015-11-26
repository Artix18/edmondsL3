#include "graph.h"

int vu[MAX_NB_NOEUDS];

char trouveCheminAugmentant(Graph* graph, int noeud, int flag)
{
	if(vu[noeud])
		return 0;
	vu[noeud]=1;
	
	if(flag==1 && graph->idAretePrise[noeud]==-1)
	{
		vu[noeud]=3;
		return 1;
	}
	
	if(flag==1)
	{
		int autreNoeud = getAutreNoeud(graph->aretes[graph->idAretePrise[noeud]], noeud);
		if(trouveCheminAugmentant(graph, autreNoeud, 1-flag))
		{
			vu[noeud]++;
			return 1;
		}
	}
	else
	{
		int i;
		for(i = 0; i < size(&graph->listeAdj[noeud]); i++)
		{
			int idArete = get(&graph->listeAdj[noeud], i);
			Arc arete = graph->aretes[idArete];
			if(arete.type==1)continue;
			
			int vois = getAutreNoeud(arete, noeud);
			
			if(trouveCheminAugmentant(graph, vois, 1-flag))
			{
				vu[noeud]++;
				return 1;
			}
		}
	}
	
	return 0;
}

Vecteur recupereChemin(Graph* graph, int noeud)
{
	int i;
	Vecteur vect;
	init(&vect, 0);
	
	int flag=0;

	while(vu[noeud] != 3)
	{
		//push_back(&vect, noeud);
		
		int voisin = noeud;
		for(i = 0; i < size(&graph->listeAdj[noeud]); i++)
		{
			int idArete = get(&graph->listeAdj[noeud], i);
			Arc arete = graph->aretes[idArete];
			if(arete.type!=flag)continue;
			
			int vois = getAutreNoeud(arete, noeud);
			if(vu[vois]<2)
				continue;
			push_back(&vect, idArete);
			voisin=vois;
			break;
		}
		
		vu[noeud]=-1;
		noeud = voisin;
		flag = 1-flag;
	}
	
	//push_back(&vect, noeud);
	return vect;
}

Vecteur trouveCheminAugmentantBiparti(Graph* graph, int affiche)
{
	int i;
	Vecteur solution;
	init(&solution, 0);
	
	for(i = 0; i < graph->nbNoeuds; i++)
		vu[i]=0;

	for(i = 0; i < graph->nbNoeuds; i++)
	{
		if(graph->idAretePrise[i]==-1 && trouveCheminAugmentant(graph, i, 0))
		{
			solution = recupereChemin(graph, i);
			if(affiche)
			{
				printf("Chemin augmentant dans le graphe biparti :\n");
				affiche_vecteur(&solution);
			}
			return solution;
		}
	}
	
	if(affiche)
		printf("Pas de chemin augmentant dans ce graphe biparti\n");
	
	return solution;
}

Vecteur couplageMaximumBiparti(Graph *graph, int affiche)
{
	int i;
	char change = 1;
	while(change)
	{
		change = 0;
		
		Vecteur augm = trouveCheminAugmentantBiparti(graph, 0);
		if(size(&augm) > 0)
		{
			change=1;
			Vecteur diff = diff_symetrique2(graph, &augm);
			
			//printf("debug\n");
			//affiche_vecteur(&augm);
			
			for(i = 0; i < size(&augm); i++)
			{
				int idArete = get(&augm, i);
				graph->aretes[idArete].type=0;
				Arc arete = graph->aretes[idArete];
				graph->idAretePrise[arete.a]=graph->idAretePrise[arete.b]=-1;
			}
			for(i = 0; i < size(&diff); i++)
			{
				int idArete = get(&diff, i);
				graph->aretes[idArete].type=1;
				Arc arete = graph->aretes[idArete];
				graph->idAretePrise[arete.a]=graph->idAretePrise[arete.b]=idArete;
			}
		}
	}
	
	Vecteur solution;
	init(&solution, 0);
	
	if(affiche)
		printf("Liste des arêtes du couplage maximum : \n");
	for(i = 0; i < graph->nbAretes; i++)
	{
		Arc arete = graph->aretes[i];
		if(arete.type==1)
		{
			push_back(&solution, i);
			printf("%d\n", i);
		}
	}
	
	return solution;
}


