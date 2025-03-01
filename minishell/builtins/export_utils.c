#include "../minishell.h"

/**
 * @brief Modifie une chaines de caracteres dans un tableau de chaines de caracteres à un index donné
 * @param array Le tableau à modifier
 * @param index L'index de la chaine à modifier (commence à 0)
 * @param new_string La nouvelle chaine à insérer
 * @return Un pointeur vers le tableau modifié ou NULL en cas d'erreur
 */
char **modify_string_in_array(char **array, char *new_string, int index)
{
	char **new_array;
	int i;
	
	if (!array || index < 0 || index >= string_array_len(array))
		return NULL;
	
	new_array = malloc(sizeof(char *) * (string_array_len(array) + 1));
	if (!new_array)
		return NULL;
	i = 0;
	while (array[i])
	{
		if (i == index)
			new_array[i] = ft_strdup(new_string);
		else
			new_array[i] = ft_strdup(array[i]);
		
		if (!new_array[i])
		{
			free_string_array(new_array);
			return NULL;
		}
		i++;
	}
	new_array[i] = NULL;
	free_string_array(array);
	return new_array;
}

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*dup;
	size_t	len;
	
	if (!src)
		return (NULL);
	len = 0;
	while (src[len] && len < n)
		len++;
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = src[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

void sort_char_array(char **array)
{
	int i, j;
	char *temp;
	
	if (!array)
		return;
	
	i = 0;
	while (array[i])
	{
		j = i + 1;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char *extract_key(const char *env_entry)
{
	char *equal_pos;
	
	if (!env_entry)
		return (NULL);
	
	equal_pos = ft_strchr(env_entry, '=');
	if (!equal_pos)
		return (ft_strdup(env_entry)); // 如果没有 `=`，直接返回整个字符串
	
	return (ft_strndup(env_entry, equal_pos - env_entry)); // 提取 `VAR`
}

int get_env_index(char **env, const char *key)
{
	int i;
	size_t key_len;
	
	if (!env || !key)
		return (-1);
	
	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
