# Procédure de démarrage



## Installation de Git

Téléchargez et installez git (https://git-scm.com/downloads) en acceptant les options par défaut.

Une fois l'opération terminée, vous devriez avoir accès aux commandes de git depuis le bouton de droite du navigateur de fichiers. 

Vous pouvez aussi installer une interface graphique de votre choix: https://git-scm.com/downloads/guis



## Accès via SSH

Vous devez avoir une clé SSH afin d'interagir de façon transparente et sécuritaire avec le serveur. 

### Création d'une clé SSH

Dans l'explorateur de fichiers, utilisez le bouton droit de votre souris puis sélectionnez, dans le menu déroulant, l'item `Git Bash Here`. Vous avez maintenant un terminal compatible avec les commandes Linux, Unix et MacOS nécessaires à l'utilisation de git.

À moins que n'avez déjà généré une clé SSH sur votre ordinateur et sachiez la récupérer, entrez la commande suivante dans le terminal Git Bash:

    ssh-keygen -t rsa -b 4096

Vous pouvez accepter les options par défaut. Lorsqu'un mot de passe vous sera demandé, vous n'avez pas à utiliser le mot de passe entré précédemment pour accéder à GitLab. Il s'agit d'un mot de passe local qui permet ou non d'utiliser la clé SSH que vous êtes en train de générer et qui peut demeurer vide.

### Vérification

Ouvrez l'explorateur de fichiers puis, via le menu déroulant activé par le bouton de droite sur/dans un dossier, sélectionnez l'item `Git Gui Here`.

Dans le menu `Help`, choisissez l'item `Show SSH Key`. Vous devriez voir une clé valide commençant par `ssh-rsa`, suivi d'un espace et d'une longue chaîne de caractères. Ceci est votre clé SSH publique.


### Autorisation de votre clé sur le serveur GitLab

Il faut maintenant configurer votre profil sur le serveur GitLab afin que votre clé personnelle SSH soit reconnue et vous permette d'accéder au contenu qui y est présent.

Rendez-vous sur la page des préférences de votre compte via l'icône de votre profil en haut à droite, en sélectionnant l'item `Settings`. Sélectionnez ensuite l'onglet `SSH Keys` dans le menu de gauche.

Copiez la clé publique consultée lors de la Vérification plus haut, puis collez son contenu dans la zone réservée à cet effet.

Vous êtes maintenant en mesure de vous connecter et vous identifier automatiquement au serveur.


