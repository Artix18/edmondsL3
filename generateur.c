// C'est mal écrit mais je ne connais presque pas le C !
// je ne sais pas pourquoi ça ne marche pas, apparemment nouveauGraphe n'est pas une fonction reconnue

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Graph* graphe_aleatoire (int nbNoeuds) {
    int t[nbNoeuds][nbNoeuds];
    int i, j, nbAretes = 0;
    int boolean, k = 0;
    Graph* g;
    
    srand(time(NULL));
    
    for (i=0; i<nbNoeuds; i++) {
        for (j=0; j<i; j++) {
            boolean = rand() % 2;
            t[i][j] = boolean;
            t[j][i] = boolean;
            if (boolean)
                nbAretes++;
            }
        t[i][i] = 0;
    }

    g = nouveauGraphe(nbNoeuds, nbAretes);
    for (i=0; i<nbNoeuds; i++) { // on remplit les aretes
        for (j=0; j<i; j++) {
            if (t[i][j]) {
                g->aretes[k].a = i;
                g->aretes[k].b = j;
                g->aretes[k].type = 0;
                k++;
            }
        }
    }

    for (i=0; i<nbNoeuds; i++) { // on remplit les listes d'adjacences
        g->listeAdj[i].capacite = nbNoeuds;
        for (j=0; j<nbNoeuds; j++) {
            if (t[i][j]) {
                g->listeAdj[i].tab[g->listeAdj[i].taille] = j;
                g->listeAdj[i].taille++;
            }
        }
    }

    return g;
}


main () {
    Graph *graph = graphe_aleatoire (10);
    affiche_graphe (graph);
}
