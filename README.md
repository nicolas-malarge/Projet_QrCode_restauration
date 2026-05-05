# Projet_QrCode_restauration

L’objectif de ce projet est de simuler une application capable de lire un QR code et de permettre l’accès au menu de différents restaurants (ici : PizzaHappy, HappySushi et BurgerHappy). Afin d’accéder à ces menus, le client devra saisir un code de la forme #### #### #### pour simuler un QR code.

Pour utiliser correctement l’application, suivez les étapes suivantes :

Compiler une première fois le Makefile.  
Dans une première console, tapez ./ExecutableServer pour lancer le serveur, qui servira de routeur.  
Dans une deuxième console, tapez ./ExecutableData pour lancer la base de données.  
Les deux premiers terminaux devraient être en attente de clients.  
Enfin, dans un troisième terminal, tapez ./ExecutableClient pour commencer.  

Dans le terminal du client, celui-ci attend un choix de l’utilisateur. Entrez le code correspondant au QR code du restaurant souhaité.

Le client devrait alors recevoir le menu désiré, tandis que les programmes server et data continueront de fonctionner en attendant l’arrivée de futurs clients.
