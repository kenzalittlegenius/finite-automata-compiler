# finite-automata-compiler
C implementation of a simplified lexical analyzer generator: regular expressions .-> AST -> NFA -> DFA -> minimal DFA


## Commandes

make clean

make

./projet test.txt

ls *.dot

make graphs


## Description du projet (in french)


Depuis l’expression rationnelle e donnée en entrée, votre Gal devra construire séquentiellement :

 — l’arbre de syntaxe abstraite T de e (construit de la gauche vers la droite comme cela a été vu en cours et en TD);
 — l’automate fini non déterministe N associé à T contenant potentiellement des ϵtransitions, par l’application de l’algorithme de McNaughton, Yamada et Thompson; 
 — l’automate fini déterministe D associé à N par application de l’algorithme de construction de sa table de transition Dtrans vu en cours; 
 — l’automate fini déterministe minimal D′ de e. Vous devrez également fournir une représentation graphique de chacun des « objets » T , N, D et D′. La création de telles représentations devra être automatisée à l’aide d’un logiciel de représentation de graphe tel que graphviz.

note à moi même : 

les fichiers .h sont les headers files. Ils contiennent les prototypes de fonctions, les structures, les constantes, les types. Ses déclarations sont utilisées par plusieurs fichiers .c.
les fichiers .o sont les fichiers objets avec les déclarations
les fichiers .c 

DFA = deterministic finite automaton
NFA = Non-deterministic Finite Automaton


