#include "graph.h"
#include <vector>

using namespace std;

int match[MAX_NB_NOEUDS];
int vvu[MAX_NB_NOEUDS];
int peres[MAX_NB_NOEUDS];
int repres[MAX_NB_NOEUDS];

/* plusieurs remarques : j'ai l'impression que l'étiquetage pair / impair ne sert à rien, puisqu'avec un dfs on se ballade uniquement sur les pairs.
   J'ai aussi l'impression que la contraction de fleurs ne change fondamentalement rien à l'algorithme et donc qu'on peut juste tout marquer sur
   le blossom, mettre la base en représentant et continuer... C'est plus facile à coder
   Le cas C n'existe pas avec un dfs.
   La source peut n'etre que dans le dfs puisque c'est toujours la même. Finalement, il ne reste que le pere...
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
    while(true)
	{
	    next=repres[next];
	    bidule[next]=1;
	    if(match[next]==-1)break;
	    next=peres[match[next]];
	}
	while(true)
	{
	    noeud=repres[noeud];
	    if(bidule[noeud])
	        return noeud;
	    noeud = peres[match[noeud]];
	}
}

int dfs(Graph* graph, int source)/*, int depart, int flag, int pere)*/
{
    //printf("debug lol : %d\n", peres[0]);
	/*mark[noeud].estMarque=1;
	mark[noeud].sommetLibreDepart=depart;
	mark[noeud].parite=flag;
	mark[noeud].precedent=pere;*/
	//printf("debug : %d\n", noeud);
	int stack[MAX_NB_NOEUDS];
	int sz=1;
	stack[0]=source;//stack.push_back(source);
	vvu[source]=1;
	while(sz>0)//!stack.empty())
	{
	    int noeud = stack[sz-1];//.back();
	    sz--;
	    //stack.pop_back();
	    for(int j = 0; j < size(&graph->listeAdj[noeud]); j++)
	    {
		    int nextArete = get(&graph->listeAdj[noeud], j);
		    int next = getAutreNoeud(graph->aretes[nextArete], noeud);
		    //printf("mdr : le %deme noeud de la liste des vois de noeud=0 est %d\n", j, next);
		    if(match[noeud]==next || repres[noeud]==repres[next])
		    {
		        //printf("la\n");
		        continue;
		    }
		    if(next==source || (match[next]!=-1 && peres[match[next]]!=-1)) //next est vvu et il est matché (et pas à nous normalement).
		    {
		        //if(source==2)
		        //    printf("wtf : %d et %d\n", match[next], peres[match[next]]);
		        //printf("lol2\n");
			    int base = trouveBase(graph, next, noeud); //repres[next]; //on a trouvé un cycle
			    //markPath(next,base);
			    //markPath(noeud,base);
			
			    int cur = noeud;
			    int prec = next;
		        char blossom[MAX_NB_NOEUDS];
		        for(int i = 0; i < graph->nbNoeuds; i++)
		            blossom[i]=0;
			    while(repres[cur] != base)
			    {
			        //printf("ici %d\n", cur);
			        blossom[repres[cur]]=blossom[repres[match[cur]]]=1;
			        //repres[repres[cur]]=repres[repres[match[cur]]]=base;
			        peres[cur] = prec;
			        prec = match[cur];
			        cur=peres[match[cur]];
			    }
			
			    /*for(int i = 0; i < graph->nbNoeuds; i++)
			    {
			        if(blossom[i])
			        {
			            repres[i]=base;
			        }
			    }*/
			    //vector<int> todo;
			    for(int i = 0; i < graph->nbNoeuds; i++)
			    {
			        if(blossom[repres[i]])
			        {
			            repres[i]=base;
			            if(!vvu[i])
			            {
			                vvu[i]=1;
			                stack[sz++]=i;//stack.push_back(i);
			            }
			        }
			    }
			    /*
			    for(int i = 0; i < graph->nbNoeuds; i++)
			    {
			        if(repres[i]==base && !vvu[i])
			        {
			            vvu[i]=1;
			            int r = dfs(graph, i);
			            if(r!=-1)
			                return r;
			        }
			    }
			    */
			    //pref est la tige, le dernier dedans est la base, et ensuite on a les deux chemins de part et d'autre de next, qui forment la corolle.
		    }
		    else if(match[next]==-1 && peres[next]==-1)
		    {
		        //printf("wesh\n");
		        peres[next]=noeud;
			    return next; //cheminAugmentant depart->...->next
		    }
		    else if(peres[next]==-1)
		    {
		        //if(noeud==2)
		        //printf("coucou en %d\n", next);
		        //if(source==3)
		        //printf("lol %d\n", next);
			    int copain = match[next];
			    //vvu[copain]=1;
			    peres[next] = noeud;
			    //peres[copain] = next;
			    //int r = dfs(graph, copain);
			    //if(r!=-1)
			    //	return r;
			    vvu[copain]=1;
			    stack[sz++]=copain;//stack.push_back(copain);
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
       // printf("bidule\n");
        if(match[i]==-1)
        {
            //TODO tout reinit
            for(int j = 0; j < graph->nbNoeuds; j++)
            {
                vvu[j]=0;
                repres[j]=j;
                peres[j]=-1;
            }
            
            int dernier = dfs(graph, i);
            
            //if(i==3)
            //    printf("dernier %d\n", dernier);
            
            while(dernier != -1)
            {
                //if(i==3)
               // printf("coucou %d\n", dernier);
                int prec = peres[dernier];
                int pprec = match[prec];
                match[prec]=dernier;
                match[dernier]=prec;
                dernier=pprec;
            }
           // printf("debug lolz, voici le match courant au depart du noeud %d : \n", i);
           // afficheMatch(graph);
        }
    }
    
    //Vecteur sol;
    //init(&sol, 0);
    int cnt=0;
    
    for(int i = 0; i < graph->nbNoeuds; i++)
    {
        if(match[i]>i)
            cnt++;
    }
    printf("Le maximum matching du graphe comporte %d aretes\n", cnt);
    afficheMatch(graph);
    
    //affiche_vecteur(&sol);
}

