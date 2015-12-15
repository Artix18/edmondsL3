#include "graph.h"

int match[MAX_NB_NOEUDS];
int vvu[MAX_NB_NOEUDS];
int peres[MAX_NB_NOEUDS];
int repres[MAX_NB_NOEUDS];

/* plusieurs remarques : j'ai l'impression que l'étiquetage pair / impair ne sert à rien, puisqu'avec un dfs on se ballade uniquement sur les pairs.
   J'ai aussi l'impression que la contraction de fleurs ne change fondamentalement rien à l'algorithme et donc qu'on peut juste tout marquer sur
   le blossom, mettre la base en représentant et continuer... C'est plus facile à coder
   Le cas C n'existe pas avec un dfs.
   La source peut n'etre que dans le dfs puisque c'est toujours la même.
*/

void afficheMatch(Graph* graph)
{
    for(int i = 0; i < graph->nbNoeuds; i++)
    {
        if(match[i]>i)
            printf("%d %d\n", i, match[i]);
    }
}

int bidule[MAX_NB_NOEUDS];

int trouveBase(Graph *graph, int next, int noeud)
{
    for(int j = 0; j < graph->nbNoeuds; j++)
        bidule[j]=0;
    while(1)
	{
	    next=repres[next];
	    bidule[next]=1;
	    if(match[next]==-1)break;
	    next=peres[match[next]];
	}
	while(1)
	{
	    noeud=repres[noeud];
	    if(bidule[noeud])
	        return noeud;
	    noeud = peres[match[noeud]];
	}
}

int dfs(Graph* graph, int source)
{
	int stack[MAX_NB_NOEUDS];
	int sz=1;
	stack[0]=source;
	vvu[source]=1;
	while(sz>0)
	{
	    int noeud = stack[sz-1];
	    sz--;

	    for(int j = 0; j < size(&graph->listeAdj[noeud]); j++)
	    {
		    int nextArete = get(&graph->listeAdj[noeud], j);
		    int next = getAutreNoeud(graph->aretes[nextArete], noeud);

		    if(match[noeud]==next || repres[noeud]==repres[next])
		        continue;
		    if(next==source || (match[next]!=-1 && peres[match[next]]!=-1))
		    {
			    int base = trouveBase(graph, next, noeud);
			
			    int cur = noeud;
			    int prec = next;
		        char blossom[MAX_NB_NOEUDS];
		        for(int i = 0; i < graph->nbNoeuds; i++)
		            blossom[i]=0;
			    while(repres[cur] != base)
			    {
			        blossom[repres[cur]]=blossom[repres[match[cur]]]=1;

			        peres[cur] = prec;
			        prec = match[cur];
			        cur=peres[match[cur]];
			    }
			
			    for(int i = 0; i < graph->nbNoeuds; i++)
			    {
			        if(blossom[repres[i]])
			        {
			            repres[i]=base;
			            if(!vvu[i])
			            {
			                vvu[i]=1;
			                stack[sz++]=i;
			            }
			        }
			    }
		    }
		    else if(match[next]==-1 && peres[next]==-1)
		    {
		        peres[next]=noeud;
			    return next; //cheminAugmentant depart->...->next
		    }
		    else if(peres[next]==-1)
		    {
			    int copain = match[next];
			    peres[next] = noeud;

			    vvu[copain]=1;
			    stack[sz++]=copain;
		    }
	    }
	}

	return -1;
}

void couplageMax(Graph *graph, int affiche)
{
    for(int i = 0; i < graph->nbNoeuds; i++)
    {
        match[i]=-1;
    }
    for(int i = 0; i < graph->nbNoeuds; i++)
    {
        if(match[i]==-1)
        {
            for(int j = 0; j < graph->nbNoeuds; j++)
            {
                vvu[j]=0;
                repres[j]=j;
                peres[j]=-1;
            }
            
            int dernier = dfs(graph, i);
            
            while(dernier != -1)
            {
                int prec = peres[dernier];
                int pprec = match[prec];
                match[prec]=dernier;
                match[dernier]=prec;
                dernier=pprec;
            }
        }
    }
    

    int cnt=0;
    
    for(int i = 0; i < graph->nbNoeuds; i++)
    {
        if(match[i]>i)
            cnt++;
    }
    if(affiche)
    {
        printf("Le maximum matching du graphe comporte %d aretes\n", cnt);
        afficheMatch(graph);
    }
}

