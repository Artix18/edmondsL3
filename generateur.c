// C'est mal écrit mais je ne connais presque pas le C !
// J'ai 2 problèmes: d'abord je ne comprends pas très bien le type Graph et je n'arrive pas à donner graphe_aleatoire sous ce type.
// L'autre problème est que ce programme renvoie toujours la même chose, cela vient surement de rand mais je ne sais pas pourquoi.
// Je suppose que le problème sera réglé quand je génèrerai plusieurs fois de suite des graphes.


#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

void graphe_aleatoire (int nbNoeuds) {
    int t[nbNoeuds][nbNoeuds];
    int i, j, nbAretes=0;
    int boolean, s = 0;

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
    
    printf("%d %d\n", nbNoeuds, nbAretes); // ici au lieu de l'afficher il faudrait le traduire en un graphe de type Graph
    for (i=0; i<nbNoeuds; i++) {
        for (j=0; j<nbNoeuds; j++)
            s = s + t[i][j];
        printf("%d ",s);
        s = 0;
        for (j=0; j<nbNoeuds; j++) {
            if (t[i][j])
                printf("%d ", j);
        }
        putchar('\n');
    }
}


main () { graphe_aleatoire (10); }
