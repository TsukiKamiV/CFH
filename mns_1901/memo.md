# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    memo.md                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luxu <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 14:38:47 by luxu              #+#    #+#              #
#    Updated: 2025/01/14 20:00:49 by yourLogin        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## MON 23 dec 2024

Objectifs:

1. Makefile
2. Readline - prompt
3. History
4. ctrl-c ctrl-d
5. R&D pour des fonctions externes

------------------------------------

>READFILE

add the -lreadline flag in the makefile flag options - ok
the prompt should be the login? how to get? -ok
to get the current working directory dynamically, use "getcwd"
to ge the username, use "getenv(USER)"
for instance, the prompt will be "username>", to see if the hostname and other stuff should be added

#attention: to make sure that there's no memory leak except for the readline function (what flag to ignore readline in valgrind??)

>HISTORY

"add_history": risk of memory leaks??

>CTRL-C/CTRL-D

signals
CTRL-C: ends the executing process
CTRL-D: ends the the minishell program

++++++++++++++++++++++++++++++++++++++++++++++++++++++++

To do during Xmas holiday:

Parsing
- not interpret unclosed quotes / special characters
- single quotes
- double quotes
- cheverons (simple & double)
- environmental variables
- $?
- edge cases

Pipe

En previlegiant le parsing, des tests simples avec un single pipe.

**Merry Christmas**
*Thankssss :)*

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Lucas - SAT 28 DEC

>RECAP
- Rangement des fichiers sources par catégories, à voir si l'arborescence convient à Luyao

- Gestion des **signaux** :
	* N'importe quel signal peut maintenant ête capturé et voir son comportement adapté
	* CTRL+D (EOF) Ok
	* CTRL+C (SIGINT) Agit comme EOF, en attente de l'exec pour interrompre le processus fils
	* CTRL+/ (SIGQUIT) Ok (Efface la ligne actuelle)
	* Documentation des signaux presque ok, il manque celle de la fonction sigaction (mainloop_handling/minishell_mainloop.c)
	* Il faudra sûrement ajouter des vérifications (interactive mode ou pas) (isatty)

- **Exec/builtins**
	* pwd et env semblent être ok (à voir pour les codes de retour ?)
	* Début d'une fonction (très moche) pour vérifier si un builtin est reconnu et l'exécute (on la changera lorsque le parsing sera ok)
	* Les codes de retour ne sont pas encore gérés, à voir si on ajoute une variable pour ça dans la structure

- Gestion de la **structure** commencée et à compléter au fil du temps, **initialisation et frees ok**

- Début de recherches sur la **suppression des erreurs valgrind avec readline** :
	* Il y a possibilité de créer des "suppression files" (https://wiki.wxwidgets.org/Valgrind_Suppression_File_Howto)
	* Apparemment les gérer dans notre contexte est assez long et compliqué, à voir si on s'attarde dessus pour l'instant

>TODO
- Gestion de l'env (ajouter un champs, en retirer un) pour pouvoir gérer les builtins export et unset
- Voir le parsing avec Luyao et définir ensemble les fonctions à avoir pour consolider les features déjà entamées (CTRL+C, parsing d'une commande avec options/arg)
- Codes de retour ($?), en attente du parsing pour gérer "echo "string"", "echo $?" et "echo -n"
- Codes de retour général (ex : command not found = 127)
- Concernant les >, <, >>, << et | il faudra sûrement s'occuper de l'exec et d'une partie du parsing avant de les implémenter mais on peut toujours créer des fonctions avec read, open ou autre pour modifier le contenu d'un fichier mais sans les implémenter
- R&D : Retanscrire les .ipynb en .md et continuer les fiches + Suppression files de valgrind
- Pour le parsing la tokenisation (strtok ou split ?) semble etre indispensable.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Luyao SAT 28 DEC

> Les delimiteurs qui peuvent apparaitre dans une commande Shell:

- Spaces and tabs
- point-vircule ";"
- Double ampersand "&&"
- Double pipe "||"
- Single pipe "|"
- Newline "\n"
- Background Execution "&"
- Redirection symbols (chevrons) >, >>, <, <<  ***(How to manage them between the spaces?)***
	* $> "Bonjour" >fichier.txt - OK
	* $> "Bonjour">fichier.txt - OK
	* $> "Bonjour" > fichier.txt OK
	* *OK pour les autres délimiters*
- Variable Assignment "=" (must NOT follow or be followed by spaces)
- Variable Expansion "$" (must NOT folloew or be follwed by spaces)

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Notes Luyao -- MON 30 DEC

Fichier ajoute - token_handling

- Afin de categoriser le string d'argument saisi, la tokenization facon "Lexical" est adoptee.
- Creation de nouveau structure "t_token" (possible sous forme liste chainee) avec token type en enum (voir header file)
- rajout de t_token dans le structure shell_data, stocke dans le structure par la fonction parse_line
- Le fichier "to_be_sorted"cree au samedi 28 DEC sera supprime. A voir si la fonction "parse line" reste dans le fichier token ou ailleurs
- **ATTENTION!!!** LES COMMANDS SONT TOKENISEES COMME ARGUMENTS, to be fixed.
- There is a token tester in the R&D ficher.
- **Memory leaks a tester**
- **Pour cette version beta de tokenization, le $? n'est pas pris en compte**
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Lucas - 31 DEC

- **Export** est prêt à être ajouté (en attente du nouveau parsing)
- **Unset** Ajouté mais reste avoir si correspond au nouveau parsing
- Ajout du **parse line à la boucle principale**
- Ajout de fonctions pour manipuler facilement un tableau de strings
- **Fix** du CTRL \ (SIGQUIT)
- Choses à voir :
	* Documentation du code ?
	* Leaks potentiels de parse line ?
	* Enfin trouver comment faire le suppress file de readline
	* Schéma utile et répartition ?
	* Gérer ac/av pour exécution sans readline (checks de leaks) ?
- env -i | ./minishell -> Faire fonctionner uniquement builtins ?

> Le lexer et le parser semblent être les prochaines étapes à continuer (voir schéma)

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Luyao JEU 02 JAN 2025

- Pour le tokenizer:
	* plus de bug pour les categories entre "COMMAND" et "ARGUMENT"
	* Les pipes doivent etre tries separement
	* La fonction "parse_line" ne retourne plus le tableau des commandes mais tout est stocke dans le structure "token"
	* Le dollar suivi par un argument sans espace -- des fonctions a faire

- Nouvelles missions:
	* trouver une solution pour refaire fonctionner les builtins deja faits

	>ETAPE 1 :
	* Parsing - Saisies invalides a faire :
		- Placement des | ou < au debut ou a la fin
		- Gestion doubles >> (valide) ou || (invalid)
		- \> sans cible ou si est bien precede d'un ARGUMENT si oui essayer d'ouvrir le fd
		- Commande vide
		- Verifier quotes (", ') si elles sont ouvertes ou fermees
		- **Norme convenue** pour ces fonctions :
			* Retourne un int qui sera le code d'erreur
			* Passer la structure (shell_data) entire en parametre (**EDIT** Non voir .h)
		- Une fonction de parsing pour KEY=value ?
		- Fonction pour split une commande avec un ou plusieurs pipes en d'autres sous commandes (char **)
	>ETAPE 2 :
		- Modifier structure de donnees pour avoir un node (token) et une autre structure avec d'autres infos (**full_cmd, fd1 (IN), fd2 (OUT))
		- Creer une structure contenant les autres structures : https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
		- Autre site pour conceptualiser la structure : https://medium.com/@migueldias3r/minishell-42-project-cd20b79404cf
		- Fonctions init + frees + handling des nouvelles structures

	> Edit
	* Structure et prototypes des fonctions qui devraient aider
	* La table de commande permettra d'avoir une table des commandes par fork
	* Utilisation d'un double pointeur pour ne pas altérer le pointeur vers la liste (ptr vers le 1er) ?
	* *Vérifier à quoi sert une variable globale dans minihell ? Pour les signaux ?*
	* Commandes de checks pour mettre à jour les structures et erreur
	* Encore et toujours +

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Fusion - Mar 07 Jan

- Ajout des commandes d'initialisation et de libération des tables de commandes + nodes
    * Reste à faire la fonction pour ajouter la table de commandes à shell_data->command_table
- Attention doublon fonctions "add_token"
- Il va falloir créer :
    * Une fonction pour ajouter et free la table de commandes dans shell_data
    * Une autre pour commencer à parser l'input et créer les tables/tokens correspondants
- Ajouter docstrings pour les fonctions ?
- Leaks ?


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Luyao Mar 07 Jan

- Doublon "add_token" fixé: gardé celle dans cmd_table_manips.c
- A voir s'il est mieux de remplacer "create_token" par "init_token_list" aussi?? (paramètre différent mais peut-être plus cohérent)
- **MODIFICATION DE TOKENIZATION**
	- Le param et la valeur de retour modifiés (voir les fonctions) - afin de gérer les tableaux et les tokens plus efficacement
- **UPDATE dans cmd_table_manips.c**:
	- init_command_table -> param devient (VOID). La fonction principale de parsing appelle d'abord "create_command_table", qui appelle ensuite init_command_table et fill_command_table pour allocation de mémoire, remplir le double tableau et les booleans etc.
	- Dans la fonction fill_command_table, un des flags détecte si présence de redir: possible d'appeler handle_redirection

TODO:
	- finir la partie EXPANDER (redirection, prep pour exec etc.)
	- Faire une fonction de test pour printer le double tableau des commandes
	- fixer memory leaks

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Luyao Jeu 09 Jan

- Update cmd_table_manips.c : cmd_table modif, une liste chainee pour prendre plusieurs tables en fonction du nombre de pipes
- Program tester dans r_and_d pour command table handling
- Essaie de gerer les heredocs, fonction "handle_heredoc" (pour le moment en commentaire, pour qu'elle puisse travailler avec les pipes)

=================================================================
UPDATE

Suite aux pb de tokenization, les modifs suivantes ont été faites:
- Remettre la fonction prepare_input (la moche). L'erreur de tokenization fixé
- Modifiées:
	- parse_line -> appelle fill_command_table au lieu de create_command_table, c'était une erreur
	- tokenize -> moins de variables, pas de changement significatifs
	- parse_tokens_into_command_table -> éviter d'assigner current->next->next pour des comportements inconnus
	- rajouts de quelques error_exit pour des cas d'erreurs
- **KNOWN BUGS**:
	Le program ne fonctionne toujours pas avec des commandes complexe (e.g. "ls -a"), seg fault dans la fonction "parse_tokens_into_command_table", mais le tester peut fonctionner. à debug ASAP


+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

## Notes Luyao Ven 10 Jan

- MAJ de cmd_table_manips.c et data_struct_utils.c pour fixer le seg fault causé par les tokens values initialisées manuellement à NULL, et free le tableau de cmd après chaque nouveau prompt
- Les tableaux de commandes en liste chaînée sont bien crées à ce jour. Une nouvelle fonction "Print_command_table" est dispo dans "/mainloop_handling/minishell_mainloop.c", ça suffit de décommenter la fonction ainsi que la ligne dans la fonction mainloop pour print
- Les mémoires allouées sont free dans le mainloop, leaks à check

---

## Notes Luyao Mar 14 Jan

- Ajoute /data_handling/redir_and_heredoc.c -- appelée par "parse_tokens_into_cmd_table" (Plus de cas d'erreurs à gérer et error msg à free dans error_exit)

---

## Notes Lucas Mer 15 Jan

- Ajout des premières fonctions d'exécutions
- Utilisation de la mainloop à nouveau possible mais peu de gestion de frees
- Fonctions de checks sur les commandes système/builtins
- Privilégier command_table->token_list à shell_data->tokens_list
- Problèmes dans les frees et init ? Valgrind indique des erreurs pour les tables et les nodes.
- Début de gestion des files descriptors dans la structure
- Voir ensemble pour faire un point en présentiel ?

---

## Notes Lucas Ven 17 et 18
- Frees des nodes/cmd tables/autres en cours de fix (**à prioriser car bloquant**)
- Il faudra reset (*free et remettre à 0*) les tokens et la table des commandes entre chaque input (voir prints des i successifs entre les commandes dans la mainloop) ?
- Ajouter à e_token_type **REDIRECTION_FILE et HEREDOC** pour les tokens ? + Supprimer **WHITESPACE** sauf si utile ailleurs ?
- Modification de shell_data->env : N'est plus le pointeur vers la première valeur de env mais un pointeur vers une copie de env (pour éviter les invalid frees)
- CTRL D refonctionne suite au point précédent
- Toutes les *erreurs* valgrind sont corrigées mais il manque des frees
* Segfault si juste un espace est entré + autres à voir

> Objectifs
=> Utilisation de shell_data->command_table->token_list
=> Leaks
=> Consolidation des fonctions de parsing existantes + exec
=> Suppression file ? **Voir r&d**
