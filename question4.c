#include "graph.h"

//TODO: il semble qu'il va falloir réécrire la structure du Graphe et le main, pour deux raisons : 
//1) Il y a des spécifications sur la page du projet du format "standard" d'un graphe.
//2) La description des chemins que j'ai choisie utilise des id d'aretes, ce qui n'existe plus dans leur représentation, et 
//   n'est pas pratique pour le sens.

int getLast(Graph *graph, Vecteur chemin, int depart)
{
	int i;
	int final=depart;
	for(i = 0; i < size(&chemin); i++)
	{
		final = getAutreNoeud(graph->aretes[get(&chemin, i)], final);
	}
	return final;
}

int getLast_bound(Graph *graph, Vecteur chemin, int depart) {
    return 3+2*size(&chemin);
}

int donneCetteArete(Graph *graph, int a, int b)
{
	int i;
	for(i = 0; i < size(&graph->listeAdj[a]); i++)
	{
		int idArete = get(&graph->listeAdj[a], i);
		Arc arete = graph->aretes[idArete];
		int autre = getAutreNoeud(arete, a);
		if(autre==b)
			return idArete;
	}
	
	return -1;
}

int donneCetteArete_bound (Graph *graph, int a, int b) {
    2+9*size(&graph->listeAdj[a]);
}

void relieDansCorolle(Graph *graph, Vecteur corolle, int dep, int fin, char flag, Vecteur* res) //on sq fin=corolle[0]
{
	int i,next,posD;
	if(dep==fin)
		return;
	
	for(i = 0; i < size(&corolle); i++)
	{
		if(get(&corolle, i) == dep)
		{
			posD = i;
			break;
		}
	}
	
	if(posD % 2 == flag) //on continue vers i>posD
	{
		int curPos=posD;
		for(next=curPos+1; curPos < size(&corolle); curPos++)
		{
			push_back(res, donneCetteArete(graph, get(&corolle, curPos), get(&corolle, next)));
			curPos=next;
		}
		push_back(res, donneCetteArete(graph, get(&corolle, curPos), get(&corolle, 0))); //conclut le cycle
	}
	else
	{
		int curPos=posD;
		for(next = posD-1; next>=0;next--)
		{
			push_back(res, donneCetteArete(graph, get(&corolle, curPos), get(&corolle, next)));
			curPos=next;
		}
	}
}

int relieDansCorolle_bound(Graph *graph, Vecteur corolle, int dep, int fin, char flag, Vecteur* res) {
    return 3+(10+2*graph->nbNoeuds)*size(&corolle);
}

//je viens de penser au fait qu'il peut y avoir un bug si la fusion est mal faite : 
//il peut y avoir plusieur arêtes entre deux corolles, et donc entre deux noeuds dans le graphe réduit.
Vecteur decompression(Graph* graph, Vecteur corolle, Vecteur cheminAugmContracte, int depart, int affiche) //on suppose que corolle est donné sous forme de cycle
{
	int i;
	
	Graph *gContra = contracte(graph, corolle,0);
	Vecteur res;
	init(&res, 0);
	int repres = get(&corolle, 0);
	int idArete = get(&cheminAugmContracte, 0);
	Arc arete = graph->aretes[idArete];
	int vk = get(&corolle, 0);//trouveBaseCorolle(corolle); //on peut supposer que vk=corolle[0]

	int last = depart;//getLast(graph, cheminAugmContracte, depart);
	
	if(depart==repres)
	{
		int nxt = getAutreNoeud(gContra->aretes[get(&cheminAugmContracte, i)], depart);
		int idAr = get(&cheminAugmContracte, 0);
		int y = getAutreNoeud(gContra->aretes[idAr], nxt);
		int c = getAutreNoeud(graph->aretes[idAr], y);

		relieDansCorolle(graph, corolle, c, vk, 0, &res);
		push_back(&res, idAr);
		last=nxt;
	}

	for(i = (depart==repres); i < size(&cheminAugmContracte); i++)
	{
		int nxt = getAutreNoeud(gContra->aretes[get(&cheminAugmContracte, i)], last);
		push_back(&res, get(&cheminAugmContracte, i));
		if(nxt==repres)
		{
			int pleine = i%2;
			int x = last;
			int areteIncidenteCorolle = get(&cheminAugmContracte, i);
			int c = getAutreNoeud(graph->aretes[areteIncidenteCorolle], x);

			relieDansCorolle(graph, corolle, c, vk, 1-pleine, &res);

			if(i+1<size(&cheminAugmContracte))
			{
				int idAr2 = get(&cheminAugmContracte, i+1);
				int y = getAutreNoeud(gContra->aretes[idAr2], nxt);
				c = getAutreNoeud(graph->aretes[idAr2], y);

				relieDansCorolle(graph, corolle, c, vk, pleine, &res);
				push_back(&res, idAr2);
				i++;
			}
		}
		last=nxt;
	}

    //obsolète
	/*if(arete.a == repres || graph->aretes[get(&CheminAugmContracte, size(&cheminAugmContracte)-1)].b==repres) //en gros
	{
		//extremité, il suffit donc de tracer le chemin jusqu'à la base.
	}
	else if(...)
	{
		//on a x1-...-xp - corolle - xp+1- ... et corolle embranchée sur (a,b) avec par ex (xp-a) pleine. On a donc
		//a est base de la corolle et xp est le sommet précédent sur la tige. On a donc juste à tracer le chemin de b à la base...
	}
	else //rien à faire
	{
		return cheminAugmContracte;
	}*/
	if(affiche)
	{
	    printf("Chemin augmentant décompressé (de taille %d) : \n", size(&res));
	    affiche_vecteur(&res);
	}
	return res;
}

int decompression_bound (Graph* graph, Vecteur corolle, Vecteur cheminAugmContracte, int depart) {
    return contracte_bound(graph, corolle, 0)+30+(3+(10+2*graph->nbNoeuds)*size(&corolle))+size(&cheminAugmContracte)*(20+2*(3+(10+2*graph->nbNoeuds)*size(&corolle)));
}
