
# Procédure de démarrage

Voici quelques instructions à suivre afin de posséder et configurer les outils nécessaires à une collaboration efficace entre les membres de votre équipe.


## Installation de Git

Téléchargez et installez git (https://git-scm.com/downloads) en acceptant les options par défaut. Vous pouvez aussi installer une interface graphique plus conviviale de votre choix: https://git-scm.com/downloads/guis

Sur Mac et Linux, l'outil peut être utilisé en lignes de commandes à partir de n'importe quelle fenêtre de terminal. 
Sur Windows, l'installation de base inclut on outil de type terminal (`Bash`) compatible avec les commandes Linux, Unix et MacOS nécessaires à l'utilisation de git. 
Dans les deux cas, l'installation inclut une interface graphique (`Gui`) de base. 

Notez que sur Windows, vous avez accès aux programmes depuis le navigateur de fichiers: en utilisant le bouton de droite sur/dans un dossier, les items `Git Bash Here` et `Git Gui Here` devraient être disponibles dans le menu déroulant.


## Accès via SSH

Vous devez avoir une clé SSH afin d'interagir de façon transparente et sécuritaire avec un serveur distant. 

### Création d'une clé SSH

Sur Mac/Linux, ouvrez une fenêtre de terminal. Pour les utilisateurs de Windows: dans l'explorateur de fichiers, utilisez le bouton de droite de votre souris puis sélectionnez, dans le menu déroulant, l'item `Git Bash Here`.

À moins que n'avez déjà généré une clé SSH sur votre ordinateur et sachiez la récupérer, entrez la commande suivante dans le terminal Git Bash:

    ssh-keygen -t rsa -b 4096

Vous pouvez accepter les options par défaut. Lorsqu'un mot de passe vous sera demandé, vous n'avez pas à utiliser le mot de passe entré précédemment pour accéder à GitLab. Il s'agit d'un mot de passe local qui permet ou non d'utiliser la clé SSH que vous êtes en train de générer et qui peut demeurer vide.

### Vérification

Ouvrez l'explorateur de fichiers puis, via le menu déroulant activé par le bouton de droite sur/dans un dossier, sélectionnez l'item `Git Gui Here`.

Dans le menu `Help`, choisissez l'item `Show SSH Key`. Vous devriez voir une clé valide commençant par `ssh-rsa`, suivi d'un espace et d'une longue chaîne de caractères. Ceci est votre clé SSH publique.


### Autorisation de votre clé sur le serveur GitLab

Il faut maintenant configurer votre profil sur le serveur GitLab afin que votre clé personnelle SSH soit reconnue et vous permette d'accéder au contenu qui y est présent.

Rendez-vous sur la page des préférences de votre compte via l'icône de votre profil en haut à droite, en sélectionnant l'item `Settings`. Sélectionnez ensuite l'onglet `SSH Keys` dans le menu de gauche.

Copiez la clé publique consultée lors de la vérification plus haut, puis collez son contenu dans la zone réservée à cet effet.

Vous êtes maintenant en mesure de vous connecter et de vous identifier automatiquement au serveur.


## Espace de travail

Vous partagerez votre travail via un dépôt dans un espace de travail qui vous est réservé dans un groupe qui a été créé pour votre équipe. Le chemin d'accès à votre espace de travail est:

    https://git.step.polymtl.ca/gbm2100-H20/gX/Y

où `X` est le numéro de votre groupe (1 ou 2) et `Y` est un identificant d'équipe qui vous a été attribuée (c.f. votre courriel d'invitation). Le chemin `gbm2100-H20/gX/Y` constitue le *namespace* de votre/vos projet/s.



### Création de votre dépôt de travail

Afin de démarrer facilement, vous pouvez faire une copie d'un projet de référence disponible dans l'espace partagé `gbm2100-H20`. À partir de votre espace de travail, consultez la section `Shared projects` et rendez-vous sur la page du projet `pstat-psoc`. 

SVP, activez la cloche de notifications associées au projet `pstat-psoc`.

*Un seul* membre de votre équipe doit faire une copie du projet dans votre espace de travail.

1. appuyez sur le bouton `fork` à droite du nom du projet;
2. sélectionnez votre espace de travail comme destination de la copie.

## Dépôt local

Vous pouvez maintenant créer un dépôt sur votre ordinateur personnel qui vous permettra de faire et partager votre travail, ainsi que d'intégrer celui de vos coéquipiers.

1. appuyez sur le bouton `clone` à côté du nom de votre projet *dans votre espace de travail* `https://git.step.polymtl.ca/gbm2100-H20/gX/eY`;
2. copiez le chemin d'accès (SSH);
3. lancez `Git Bash` dans le répertoire de votre ordinateur où vous souhaitez travailler puis entrez la commande suivante:

    git clone url_copie

Vous avez dans le répertoire ainsi créé (`pstat-psoc`) un *workspace* de PSoC Creator qui vous permettra de vous lancer rapidement dans votre projet. Vous pouvez maintenant faire des modifications à votre guise et les partager avec vos coéquipiers.

### Préparation à la collaboration

Pour finir, assurez-vous de travailler dans une branche de développement (`dev`), et non sur la branche `master`:

    git checkout dev

Vous pouvez bien sûr créer de nouvelles branches selon vos besoins et les partager avec vos coéquipiers.


# Ressources

Vous pouvez consulter de nombreuses ressources pour approfondir vos connaissances, notamment:

- un [petit guide visuel](https://agripongit.vincenttunru.com) illustrant les concepts de base;
- un [guide plus complet](http://www-cs-students.stanford.edu/~blynn/gitmagic/intl/fr/) en français;
- un [court tutoriel](https://gitguide.readthedocs.io/en/latest/index.html) en anglais pour l'essentiel;
- un [site instructif](https://www.atlassian.com/fr/git/tutorials/what-is-version-control), notamment au sujet de la [collaboration](https://www.atlassian.com/fr/git/tutorials/syncing) et des [méthodes de travail](https://www.atlassian.com/fr/git/tutorials/comparing-workflows)
- les [notions de base](https://docs.gitlab.com/ee/gitlab-basics/README.html) sur GitLab

