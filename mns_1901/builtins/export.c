#include "../minishell.h"


/**
 * @brief Modifie une chaines de caracteres dans un tableau de chaines de caracteres à un index donné
 * @param array Le tableau à modifier
 * @param index L'index de la chaine à modifier (commence à 0)
 * @param new_string La nouvelle chaine à insérer
 * @return Un pointeur vers le tableau modifié ou NULL en cas d'erreur
 */
char	**modify_string_in_array(char **array, char *new_string, int index)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!array || !*array || index < 0 || index >= string_array_len(array))
		return (NULL);
	new_array = malloc(sizeof(char *) * (string_array_len(array) + 1));
	if (!new_array)
		return (NULL);
	while (array[i])
	{
		if (i == index)
		{
			new_array[i] = ft_strdup(new_string);
			if (!new_array[i])
				return (free_string_array(new_array), NULL);
		}
		else
		{
			new_array[i] = ft_strdup(array[i]);
			if (!new_array[i])
				return (free_string_array(new_array), NULL);
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
/**
 * @brief Export builtin, modifie ou ajoute une variable d'environnement
 * @param env Le tableau des arguments
 * @param cmd Le tableau des commandes tokenisees
 */
// int	export_builtin(char **env, char **cmd)

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	char	**array;
// 	char	**new_array;
// 	int i;

// 	array = malloc(sizeof(char *) * 4);
// 	array[0] = ft_strdup("Hello");
// 	array[1] = ft_strdup("World");
// 	array[2] = ft_strdup("!");
// 	array[3] = NULL;

// 	new_array = modify_string_in_array(array, "Bonjour", 1);

// 	i = 0;
// 	while (new_array[i])
// 	{
// 		printf("New array[%d]: %s\n", i, new_array[i]);
// 		printf("Old array[%d]: %s\n", i, array[i]);
// 		i++;
// 	}

// 	free_string_array(array);
// 	free_string_array(new_array);
// 	return (0);
// }
