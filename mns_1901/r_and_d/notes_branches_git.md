# Notes sur les branches Git
--------------------------

*Note :Il est impportant de faire un premier commit avant de créer une branche (ou de créer la branche main)*
*On ajoute généralement une branche pour travailler sur une fonctionnalité ou une tâche spécifique (Gestion erreur, ajout d'une fonctionnalité...)*

## Créer une branche
> Créer une branche et aller dessus. -b permet de créer la branche si elle n'existe pas.
`$> git checkout -b nom_de_la_branche`

############

## Modifier nos fichiers sources
> Une fois ajoutés, on peut add et commit pour valider et créer un commit localement.
`$> git add minishell.c minishell.h Makefile`
`$> git commit -m "Message du commit"`
`$> git push origin nom_de_la_branche`

############

## Recevoir les modifications
> Les modifications sont maintenant accessibles. On récupère d'abord les branches sans les fusionner avec `fetch`
`$> git fetch`
> `-r` permet de voir les branches distantes
`$> git branch -r`

############

## Changer de branche et fusionner les modifications
> On se place sur la branche et on récupère les modifications
`$> git checkout nom_de_la_branche`
`$> git pull origin nom_de_la_branche`

############

## Fusionner les modifications
> On fusionne les modifications de la branche avec la branche principale
`git checkout main`
`$> git merge nom_de_la_branche`

############

## Gérer un conflit
> On risque d'être confrontés à des conflits entre nos deux branches. On a je crois 2 solutions :
> Un conflit se présente sous la forme suivante :

```
<<<<<<<<<<<<< HEAD
printf("Hello World\n");
========
printf("Bonjour le monde\n");
>>>>>>>>>>>>> nom_de_la_branche
```

> On peut soit modifier manuellement le fichier en question
`printf("Bonjour le monde / Hello World !\n");`
`git add fichier.c`
`git commit -m "Résolution du conflit"`
`git push origin main`

## Annuler un commit (non push)
> Si on a commit trop tôt on peut l'annuler avec `reset`
`$> git reset HEAD~1`
> HEAD correspond à la dernière version du commit, HEAD~1 à l'avant-dernière etc ?

############

## Comparer les modifications depuis le dernier commit
> On peut comparer les modifications depuis le dernier commit avec `diff`
`$> git diff HEAD~1`

+--------------------------------------------------+
| Commande             | Description               |
+--------------------------------------------------+
| git init             | Initialiser un dépôt Git  |
+--------------------------------------------------+
| git checkout -b      | Créer une branche si elle |
| nom_branche          | n'existe pas              |
+--------------------------------------------------+
| git push origin      | Envoi les modifications   |
| nom_branche          | Vers la branche distante  |
|                      | (main, debug-branch...)   |
+--------------------------------------------------+
| git pull origin      | Récupère les modifications|
| nom_branche          | de la branche distante    |
+--------------------------------------------------+
| git merge nom_branche| Fusionne les modifications|
+--------------------------------------------------+
| git fetch            | Récupère les branches     |
|                      | distantes sans les        |
|                      | fusionner                 |
+--------------------------------------------------+
| git branch -r        | Affiche les branches      |
|                      | distantes                 |
+--------------------------------------------------+
| git reset HEAD~1     | Annule le dernier commit  |
|                      | (non push)                |
+--------------------------------------------------+
| git diff             | Compare les modifications |
+--------------------------------------------------+