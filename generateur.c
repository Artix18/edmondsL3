#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void graphe_aleatoire (int nbNoeuds) {
    int t[nbNoeuds][nbNoeuds];
    int i, j, nbAretes = 0;
    int boolean;
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
    
    printf("6\n");
    printf("%d %d\n", nbNoeuds, nbAretes);
    for (i=0; i<nbNoeuds; i++) {
        int s = 0;
        for (j=0; j<nbNoeuds; j++) {
            if (t[i][j])
                s++;
        }
        
        printf("%d ", s);
        for (j=0; j<nbNoeuds; j++) {
            if (t[i][j])
                printf("%d ", j);
        }
        putchar('\n');
    }
}

int graphe_aleatoire_bound (int nbNoeuds) {
    return 6+nbNoeuds*nbNoeuds*5;
}

int main () 
{
    graphe_aleatoire (300);
    return 0;
}
