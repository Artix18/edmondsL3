// C'est mal écrit mais je ne connais presque pas le C !
// problème: je ne comprends pas très bien le type Graph et je n'arrive pas à donner graphe_aleatoire sous ce type.

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void graphe_aleatoire (int nbNoeuds) {
    int t[nbNoeuds][nbNoeuds];
    int i, j, nbAretes=0;
    int boolean, s = 0;
    
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
    
    printf("%d %d\n", nbNoeuds, nbAretes);
    // ici au lieu de l'afficher il faudrait le traduire en un graphe de type Graph
    // sinon je les mets dans des .txt et on les exécute manuellement
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
