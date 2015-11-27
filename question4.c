#include "graph.h"

//TODO: il semble qu'il va falloir réécrire la structure du Graphe et le main, pour deux raisons : 
//1) Il y a des spécifications sur la page du projet du format "standard" d'un graphe.
//2) La description des chemins que j'ai choisie utilise des id d'aretes, ce qui n'existe plus dans leur représentation, et 
//   n'est pas pratique pour le sens.

Vecteur decompression(Graph* graph, Vecteur corolle, Vecteur cheminAugmContracte)
{
	Graph *gContra = contracte(graph, corolle);
	int repres = get(&corolle, 0);
	int idArete = get(&cheminAugmContracte, 0);
	Arc arete = graph->aretes[idArete];

	if(arete.a == repres || graph->aretes[get(&CheminAugmContracte, size(&cheminAugmContracte)-1)].b==repres) //ou b, mais hum.
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
	}
}
