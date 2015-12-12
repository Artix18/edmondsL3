#include "graph.h"

Mark mark[MAX_NB_NOEUDS];

/* plusieurs remarques : j'ai l'impression que l'étiquetage pair / impair ne sert à rien, puisqu'avec un dfs on se ballade uniquement sur les pairs.
   J'ai aussi l'impression que la contraction de fleurs ne change fondamentalement rien à l'algorithme et donc qu'on peut juste tout marquer sur
   le blossom et continuer... C'est moins chiant à coder
   Le cas C n'existe pas avec un dfs.
   La source peut n'etre que dans le dfs puisque c'est toujours la même. Finalement, il ne reste que le pere...
*/
Vecteur prefixe(int noeudA, int noeudB)
{
	Vecteur truc;
	return truc;
}

int dfs(Graph* graph, int noeud)/*, int depart, int flag, int pere)*/
{
	/*mark[noeud].estMarque=1;
	mark[noeud].sommetLibreDepart=depart;
	mark[noeud].parite=flag;
	mark[noeud].precedent=pere;*/
	for(int j = 0; j < size(&listeAdj[noeud]); j++)
	{
		int next = get(&listeAdj[noeud], j);
		if(graph->idAretePrise[next]==-1 && mark[next].estMarque==0)
		{
			return next; //cheminAugmentant depart->...->next
		}
		else if(mark[next].estMarque == 0)
		{
			int copain = getAutreNoeud(get(graph->aretes,graph->idAretePrise[next]), next);
			mark[next].estMarque = mark[copain].estMarque = 1;
			mark[next].sommetLibreDepart = mark[copain].sommetLibreDepart = mark[noeud].sommetLibreDepart;
			mark[next].parite=1;
			mark[copain].parite=0;
			mark[next].precedent=noeud;
			mark[copain].precedent=copain;
			int r = dfs(graph, copain);
			if(r!=-1)
				return r;
		}
		else //TODO
		{
			Vecteur pref = prefixe(next, noeud);
			//pref est la tige, le dernier dedans est la base, et ensuite on a les deux chemins de part et d'autre de next, qui forment la corolle.
		}
	}

	return -1;
}
