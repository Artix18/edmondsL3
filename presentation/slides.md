% L'algorithme d'Edmonds
% Jules Pondard, Joseph, Lucas
% 1er Janvier 2016

# Quel est le problème ?

## Rappel du problème

* Etant donné un graphe non orienté, on souhaite sélectionner un ensemble d'arêtes tel que :   
	* Cet ensemble soit le plus grand possible.   
	* Chaque noeud du graphe apparait au plus dans une arête de l'ensemble.
  La liste des arêtes d'un tel ensemble est appelée **couplage maximum**.

* ***L'objectif est de trouver un tel couplage en temps polynomial.***

## Cas particulier

On peut s'intéresser au problème du couplage maximum dans des graphes particuliers. 

### Exemple, graphe biparti  
- N personnes numérotées de 1 à N et N vélos numérotés de 1 à N. Chaque personne aime certains vélos : on donne pour chaque personne la liste des vélos qu'elle aime bien.   
- Est-il possible d'attribuer un vélo à chaque personne ?
- C'est le problème du *couplage maximum dans un graphe biparti*.

## Résolution particulière

On se donne la représentation suivante pour un graphe biparti.   
Les arêtes coloriées appartiennent au couplage.
<!--![coucou](biparti1.png)-->
\center\includegraphics[height=4.5cm]{graphebiparti1.png}

Comment déterminer le couplage maximum ?

## Résolution particulière (2)

Quel que soit le couplage, il est maximum ssi il n'existe pas de chemin augmentant (image needed).

### Algorithme de couplage dans un graphe biparti

~~~{.python .numberLines}
changement = VRAI
while (changement):
	changement = FAUX
	cheminAugmentant = trouveCheminAugmentant()
	if (cheminAugmentant != VIDE):
		prendreLeCheminAugmentant()
		changement = VRAI
~~~

# Généralisation
##

\center\includegraphics[height=6.5cm]{edmonds2.jpg}

## Idée générale de l'algorithme

### Résultat admis

Dans un graphe général, un couplage est maximum si et seulement si il n'existe pas de chemin augmentant.

Ceci nous conduit à l'idée suivante : *faire comme précédemment !*   
Il suffit de boucler tant qu'on 

## Problème : existence de cycles impairs

Pour trouver un chemin augmentant, on ne peut plus procéder exactement comme avant à cause de la présence de cycles impairs.
TODO: image illustrant ça.

## Solution : la contraction de fleurs

Conformément au lemme admis dans le polycopié, on peut continuer à chercher un chemin augmentant sur le graphe contracté, dans lequel le cycle impair,
appelé fleur, a été fusionné en un seul noeud. C'est l'**algorithme d'Edmonds**.

### Remarques
* Nous avons choisi l'ordre du DFS sur les arêtes en conservant l'algorithme décrit dans le sujet.
* Le pseudo-code qui va suivre diffère légèrement du code que nous avons écrit, pour faciliter la compréhension.
* Comme signalé dans le rapport, nous pensons que la fonction trouveCorolle n'a pas besoin d'être employée.

## Blossom Algorithm

### Pseudo-code de la fonction trouveCheminAugmentant

\lstinputlisting[language=python]{cheminAugm_p1.pseudo}

## Suite du code

### Suite de la fonction trouveCheminAugmentant

\lstinputlisting[language=python]{cheminAugm_p2.pseudo}

## Fonction jsaispasquoi

~~~{.c .numberLines}
lol
~~~

## Analyse de la complexité

* On peut augmenter le truc N fois. A chaque fois on fait du N. N^3 (ou N^4 si on reste sur leur idée ici).

# Notre implémentation

## Le parcours global

TODO

## La contraction de fleurs

TODO

## Complexité

La complexité passe ainsi en N^3

# Aspects techniques et difficultés

## Autour de la structure générale de l'algorithme

* Nous avons changé à plusieurs reprises d'avis concernant la manière la plus simple de représenter le graphe en mémoire.
	* Que ce soit pour les arêtes
	* Ou pour la façon dont on représente un couplage

. . .

* Nous ne savions pas vraiment quel était le format attendu pour permettre à l'utilisateur de tester chaque fonction.
	* Nous avons choisi de faire un main qui permet en rentrant un certain numéro de sélectionner la fonction à tester
	* Cela présente l'inconvénient de faire croire à une homogénéité des formats d'entrée.

## Autour de la structure générale de l'algorithme (suite)

* Il était écrit dans le sujet que l'on pouvait obtenir la complexité de V^3, où V est le nombre de noeuds.
	* Nous avons cherché à obtenir cette complexité
	* Tout en simplifiant la manière de coder l'algorithme
	
	. . .
	
	* L'algorithme qui en résulte est pour nous assez satisfaisant : 
		* Il est plus efficace en termes asymptotiques, O(V^3) au lieu de O(V^4).
		* Il épargne une vraie fusion des noeuds lors de la contraction des fleurs.

## Autour du langage C

L'un d'entre nous était déjà à l'aise avec le langage C et à sa bibliothèque standard.
Voici quelques points que nous avons été amenés à considérer.

. . .

* Il est nécessaire de passer par l'allocation dynamique pour représenter un graphe peu dense efficacement.
	* En effet, chaque noeud a un nombre variable d'arêtes. Si le graphe comporte 5N arêtes par exemple, 
	un noeud peut en posséder N et la plupart des autres 0. Il serait alors dommage de stocker N arêtes par noeud !
	* Nous avons, à cet effet, réimplémenté la structure de Vecteur étudiée en TD.
	. . .
		* *Nous l'avions d'ailleurs bugée...*
. . .
* Nous avons regretté que le C ne permette pas de définir des fonctions dans ses structures.
  Il est désagréable de passer un pointeur sur l'objet à chaque fonction pour simuler un simple "obj->foo()".
. . .
* Le C n'est pas simple à débugger à la différence du langage OCaml. 
  Nous avons passé du temps à faire des backtrace sur GDB pour trouver le segfault !

## Autour de la variation de l'algorithme que nous avons introduite

TODO

# Tests et performances

## Un générateur de tests

## Des sites pour tester

## De beaux graphiques

# Conclusion

Si nous avions eu plus de temps ...

## Des listes numérotées

1. Récupérer le projet
2. Installer `pandoc`
3. Installer les dépendances
    a. `texlive-latex-base`
    b. `latex-beamer`
4. Installer un lecteur (`impressive`)
5. `make run`

## Des citations

Celle-ci est de [*Mitch Resnick*](https://en.wikipedia.org/wiki/Mitchel_Resnick).

> If you learn to read, you can then read to learn.\
> If you learn to code, you can then code to learn.[^ted]

[^ted]: \tiny<http://www.ted.com/talks/mitch_resnick_let_s_teach_kids_to_code.html>

## Des apparitions

Par étapes :

> - d'abord…
> - ensuite…
> - enfin…

## D'autres apparitions

D'abord un paragraphe…

. . .

Puis un autre

*(ça ne marche pas avec pandoc 1.9.4.2, mais ça marche avec 1.12.2.1, vérifiez
votre version)*

## Mise en forme

| Il y a 2 types de personnes :
|   ceux qui comprennent la récursivité et
|   ceux qui ne comprennent pas qu'il y a 2 types de personnes :
|     ceux qui comprennent la récursivité et
|     ceux qui ne comprennent pas qu'il y a 2 types de personnes :
|       ceux qui comprennent la récursivité et
|       ceux qui…


# Spécial \LaTeX /Beamer

## Du spécifique

Certaines choses n'existent pas nativement en *Pandoc Markdown*, il suffit donc
d'utiliser du \LaTeX.

## Des blocks spécifiques

\begin{alertblock}{Alerte}
Ceci est une alerte
\end{alertblock}

\begin{exampleblock}{Exemple}
Ceci est un exemple
\end{exampleblock}

## Images

Les images sont supportées par *Markdown*, mais on ne peut pas spécifier la
taille. Il est donc pratique d'utiliser directement \LaTeX.

----

\center\includegraphics[height=6.5cm]{croissance.jpg}

## Des maths

Avec des formules :

$$
\frac{\pi}{4}=\int_0^1 \sqrt{1-x^2}\mathrm dx
$$

# À vous

## Essayez

    sudo apt-get install pandoc \
                         texlive-latex-base \
                         texlive-lang-french \
                         latex-beamer \
                         impressive
    git clone http://git.rom1v.com/mdbeamer.git
    cd mdbeamer
    make run

## Adaptez

----------- ----------------------------
  la source \code{slides.md}

   le thème \code{beamerthemeCustom.sty}
----------- ----------------------------

## Un thème en 2 minutes

Définissez vos 3 couleurs :

\scriptsize

~~~latex
\definecolor{Color1}{HTML}{25567B}
\definecolor{Color2}{HTML}{033E6B}
\definecolor{Color3}{HTML}{66A3D2}
~~~

\normalsize

Changez les logos :

\scriptsize

~~~latex
\titlegraphic{\includegraphics[height=1.5cm]{avatar.png}}
\logo{\includegraphics[height=1.5cm]{gnulogo.png}}
~~~

# Voir aussi

## Des liens

\scriptsize

pandoc
  ~ <http://johnmacfarlane.net/pandoc/demo/example9/pandocs-markdown.html>
pour beamer
  ~ <http://johnmacfarlane.net/pandoc/demo/example9/producing-slide-shows-with-pandoc.html>
en français
  ~ <http://enacit1.epfl.ch/markdown-pandoc/>
