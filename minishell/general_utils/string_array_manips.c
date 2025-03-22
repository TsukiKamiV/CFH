#include "../minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

/**
 * @brief Calcule la taille d'un tableau de chaines de caracteres (commence à 0)
 * @param array Le tableau a mesurer
 * @return La taille du tableau (int)
 */
int		string_array_len(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
/**
 * @brief Copie un tableau de chaines de caracteres
 * @param array Le tableau a copier
 * @return Un pointeur vers le tableau copie
 */
//char	**copy_string_array(char **array)
//{
//	char	**new_array;
//	int		i;
//
//	i = 0;
//	if (!array || !*array)
//		return (NULL);
//	new_array = malloc(sizeof(char *) * (string_array_len(array) + 1));
//	if (!new_array)
//		return (NULL);
//	while (array[i])
//	{
//		new_array[i] = ft_strdup(array[i]);
//		if (!new_array[i])
//		{
//			free_string_array(new_array);
//			return (NULL);
//		}
//		i++;
//	}
//	new_array[i] = NULL;
//	return (new_array);
//}

char	**copy_string_array(char ** array)
{
	int		i;
	char	**dest;
	
	i = 0;
	if (!array || !*array)
		return (NULL);
	while (array[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (array[i])
	{
		dest[i] = ft_strdup(array[i]);
		if (!dest[i])
		{
			while (i > 0)
				free (dest[--i]);
			free (dest);
			return (NULL);
		}
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

/**
 * @brief Ajoute une chaine de caracteres a la fin d'un tableau de chaines de caracteres
 * @param array Le tableau a modifier
 * @param new_string La chaine a ajouter
 * @return Un pointeur vers le tableau modifie
 *
 * @note Si le tableau est vide ou NULL, il est cree et la nouvelle chaine est ajoutee
 * @note Ne free pas le tableau d'origine
 */
char	**add_string_to_array(char **array, char *new_string)
{
	char	**new_array;
	int		i;

	i = 0;
	if (!array || !*array) // Si le tableau est vide ou NULL
	{
		new_array = malloc(sizeof(char *) * 2);
		if (!new_array)
			return (NULL);
		new_array[0] = ft_strdup(new_string);
		if (!new_array[0])
			return (free_string_array(new_array), NULL); // Return peut exécuter plusieurs instructions et retourne la dernière instruction ex
		new_array[1] = NULL; // NULL pour terminer
		return (new_array);
	}
	new_array = malloc(sizeof(char *) * (string_array_len(array) + 2)); // +2 pour la nouvelle chaine et le NULL
	if (!new_array)
		return (NULL);
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
			return (free_string_array(new_array), NULL);
		i++;
	}
	new_array[i] = ft_strdup(new_string); // Ajout de la nouvelle chaine
	if (!new_array[i])
		return (free_string_array(new_array), NULL);
	new_array[i + 1] = NULL; // NULL pour terminer le nouveau tableau
	return (new_array);
}

/**
 * @brief Supprime une chaine de caracteres d'un tableau de chaines de caracteres
 * @param array Le tableau a modifier
 * @param index L'index de la chaine a supprimer (commence a 0)
 * @return Un pointeur vers le tableau modifie
 */
char	**remove_string_from_array(char **array, int index)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0; // Index du nouveau tableau
	// Si le tableau est vide ou NULL, ou si l'index est superieur a la taille du tableau
	if (!array || !*array || index < 0 || index >= string_array_len(array))
		return (NULL);
	new_array = malloc(sizeof(char *) * string_array_len(array));
	if (!new_array)
		return (NULL);
	while (array[i])
	{
		if (i != index)
		{
			new_array[j] = ft_strdup(array[i]);
			if (!new_array[j])
				return (free_string_array(new_array), NULL);
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	free_string_array(array);
	return (new_array);
}

// int main(void)
// {
// 	char	**array;
// 	char	**new_array;
// 	int		i;

// 	// array = malloc(sizeof(char *) * 4);
// 	// array[0] = ft_strdup("Hello");
// 	// array[1] = ft_strdup("World");
// 	// array[2] = ft_strdup("!");
// 	// array[3] = NULL;
// 	// new_array = copy_string_array(array);
// 	// i = 0;
// 	// while (new_array[i])
// 	// {
// 	// 	printf("%s\n", new_array[i]);
// 	// 	i++;
// 	// }
// 	// free_string_array(array);
// 	// free_string_array(new_array);


// 	// array = malloc(sizeof(char *) * 1);
// 	// // array[0] = ft_strdup("Hello");
// 	// // array[1] = ft_strdup("World");
// 	// // array[2] = ft_strdup("!");
// 	// // array[3] = NULL;

// 	// array[0] = NULL;
// 	// new_array = add_string_to_array(array, "How are you?");
// 	// i = 0;
// 	// while (new_array[i])
// 	// {
// 	// 	printf("%s\n", new_array[i]);
// 	// 	i++;
// 	// }

// 	array = malloc(sizeof(char *) * 4);
// 	array[0] = ft_strdup("Hello");
// 	array[1] = ft_strdup("World");
// 	array[2] = ft_strdup("!");
// 	array[3] = NULL;

// 	new_array = remove_string_from_array(array, 0);
// 	i = 0;
// 	while (i <= string_array_len(new_array))
// 	{
// 		printf("Original : %s\n", array[i]);
// 		printf("New array : %s\n", new_array[i]);
// 		i++;
// 	}

// 	//free_string_array(array);
// 	printf("Len array = %d\n", string_array_len(array));
// 	printf("Len new array = %d\n", string_array_len(new_array));
// 	free_string_array(new_array);
// 	free_string_array(array);

// 	return (0);
// }
