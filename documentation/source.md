# Documentation du code source

Il est de loin préférable de documenter le code à même les fichiers sources, plutôt que de maintenir un document indépendant.
Ceci permet de conserver différentes versions et de suivre l'évolution du projet, mais surtout de s'assurer que la documentation est toujours en phase avec le code.

## Documentation spécifique au langage

Plusieurs langages modernes proposent leur propre méthode et outils de documentation.

Par exemple, le langage Java inclut l'outil [javadoc](https://www.oracle.com/technetwork/articles/java/index-137868.html) qui peut générer un site interactif de documentation à partir de commentaires adéquatement formatés. Python utilise les [docstrings](https://www.python.org/dev/peps/pep-0257/) qui peuvent être utilisés par [sphinx](https://www.sphinx-doc.org/en/master/), un outil très flexible de génération de documentation.

## Langages C, C++

Les langages C et C++ ne disposent intrinsèquement pas d'outils de documentation. 
Par ailleurs, [doxygen](http://www.doxygen.nl) s'est imposé comme [standard *de-facto*](http://www.doxygen.nl/projects.html) et offre essentiellement toutes les fonctionnalités de javadoc.

Il suffit d'inclure quelques balises au sein de commentaires respectant un format spécifique pour que l'outil soit en mesure de générer un site html interactif ou un un document pdf détaillé.

    /**
    * \file main.c
    * \brief Programme de tests.
    * \author Moi
    *
    * Programme de test pour ...
    * ...
    */

    /**
    *  \brief Description résumé de la fonction.
    *
    *  Description détaillée...
    */
    void my_func() {
        int var; ///< Description de la variable.
    }

Un tutoriel en français est disponible [ici](https://franckh.developpez.com/tutoriels/outils/doxygen/).

Ce guide sera complété ultérieurement...
