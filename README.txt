
Projet: Star Wars space shooter

Composition équipe:

	Emile Valotaire
	Alexandre Cox

Description: 

Le jeu est composé d'un vaisseau 
qui se déplace vers la droite.
Il tire les autres vaisseaux de l'empire
et les astéroids qu'ils croisent.
Le but du jeu est de tuer le plus de
vaisseau ennemis sans se faire toucher.

Objectifs:

Phase 1: Apprendre SDL2.

Phase 2: Afficher des images avec SDL2

Phase 3: Faire supperposer les images avec SDL2

Phase 4: Utiliser les threads de SDL2. La gestion/communication
	 inter-threads à pris une bonne partie du temps.

Phase 5a: Construire un vaisseau pouvant se déplacer et être afficher.

Phase 5b: Avoir un vaiseau Joueur diriger avec le clavier, direction avec
	  les fleches, tir avec W, Q pour quité.

Phase 6: Ajouter la collision des lasers et
         des vaisseaux. (partiel)

Phase 7: Ajouter du son lorsqu'on tire.

Phase 8: Ajouter un score lorsqu'on tue des
         ennemis.

Phase 9: Contruire des ennemis pouvant tirer. (non complété)

Phase 10: Ajouter la collision avec les astéroides
          et les vaisseaux. (non complété)

Phase 11: Ajouter des vagues ennemis personnalisées. (non complété)

Phase 12: Ajouter un Boss final. (non complété)

Phase 13: Ajouter des bonus bouvant améliorer
          nos lasers. (non complété)

Phase 14: Ajouter des niveaux supplémentaires. (non complété)

Structure:
Le programme comprend un main() qui initialise le jeu:
-initialisation des composantes SDL, tel que le renderer.
-Load les textures, animations, sons, la fenêtre.
-Début du timer pour la fréquence d'affichage à l'écran
-Début du thread qui spawn nos ennemis
-Début du thread de contrôle du vaiseau joueur.
Par la suite, le main s'occupe d'appeler la méthode d'affichage à l'écran.

Le jeu est composé d'entités volantes qui hérite tous de la classe
EntiteVolante, à l'exception de CEsquadronTie qui sert à englobé un
groupe d'objets Ennemis pour permettra (futur) des actions de groupe.

chaque entité (ou groupe d'entité) est gérer par son propre thread.

Une entié est rajouté au jeu en passant par la classe GameWorld, qui contient
les conteneurs et itérateurs nécessaire pour stocker un pointeur vers chaque entités.
C'est l'objet GameWorld qui permet la communication inter-thread (intéraction entre
objet, intéraction avec le renderer).

Nombre d'heures:

Nous avons passé au moins 3 heures en laboratoire
pour la sélection de nos objets et l'élaboration d'un
programme brouillon.
Nous avons passé plusieurs heures à comprendre SDL2 avec
un tutorial de 40 chapitres sur le web.
Nous avons pris 8 heures le vendredi 8 pour 
pour synchroniser nos parties de projets et débugger.

Fonctionnement:

1.Connecter au serveur Linux:

Host :		etunix.uqac.ca
Nom d'usager : 	8pro114_17
Mot de passe : 	usRwJFmj4%Kv