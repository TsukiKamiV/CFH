# Créer et appliquer un suppression file valgrind
----

## Lancer minishell avec valgrind
Valgrind dispose de plusieurs arguments. L'une d'elle est `--gen-suppressions=all`. Cette option permet de générer un fichier de suppression pour les erreurs de valgrind. Pour cela, il suffit de lancer la commande suivante :

```bash
valgrind --gen-suppressions=all --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
```

- Il peut être utile d'utiliser l'option `--log-file=valgrind.log` pour enregistrer les erreurs dans un fichier qui peut être très volumineux avec readline.

## Créer un fichier de suppression à partir du fichier de logs valgrind
On obtiendra un fichier avec le **retour de valgrind et des erreurs trouvées** ainsi que du **contenu entre accolades** `{}`. Il suffit de *copier ce contenu dans un fichier* `suppr_file.supp` par exemple. Le fichier étant long, on utilise une commande pour ne garder que le contenu qui nous intéresse :

```bash
sed -n '/^{/,/^}/ {
    s/}\s*{/} {/g    # Ajoute un espace entre } et {
    s/}/}\n/g        # Ajoute un retour à la ligne après }
    p                # Imprime le contenu modifié du bloc
}' valgrind.log > suppr_file.supp
```
*Il existe peut être plus simple qu'une regex pour gérer ça.*

## Attention
Il est probable que le fichier de suppression ne soit pas parfait. Avec cette méthodologie nos leaks se trouvent pris en compte. Il faut donc supprimer à la main les erreurs qui ne sont pas des leaks de readline.
*Un fichier de suppression existe déjà et semble bon*.
Voici une contre mesure **optionnelle** pour récupérer les erreurs de valgrind sans readline :

```bash
awk '
  /^{$/ { block=""; inside=1 }
  {
    block = block ORS $0
  }
  /}/ {
    inside=0
    # On teste si le bloc ne contient PAS 
    # l’un des symboles de readline :
    if (block !~ /(readline|rl_|add_history|alloc_history_entry|libreadline\.so|malloc|xmalloc|minishell_mainloop|fun:main)/) {
      print block
    }
    block=""
  }
' my_supp.supp
```
Si awk ne retourne rien, c'est que le fichier de suppression est bon. Autrement, il faudra le modifier à partir de ce retour.