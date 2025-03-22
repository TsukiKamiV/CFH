#include "../minishell.h"

char	*ft_strjoin_3(const char *s1, const char *s2, const char *s3)
{
	char	*ret;
	size_t	len1, len2, len3, total_len;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	total_len = len1 + len2 + len3;
	ret = malloc(total_len + 1);
	if (ret == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(ret, s1, len1);
	if (s2 != NULL)
		ft_memcpy(ret + len1, s2, len2);
	if (s3 != NULL)
		ft_memcpy(ret + len1 + len2, s3, len3);
	ret[total_len] = '\0';
	return (ret);
}

int	update_env_entry(char ***env, const char *var, const char *new_entry, size_t var_len)
{
	int	i;
	char *dup_entry;

	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], var, var_len) && (*env)[i][var_len] == '=')
		{
			free((*env)[i]);
			dup_entry = ft_strdup(new_entry);
			if (!dup_entry)
				return (0);
			(*env)[i] = dup_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

void	append_env_entry(char ***env, const char *new_entry, int i)
{
	char	**new_env;
	int		j;

	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return;
	j = 0;
	while ((*env)[j])
	{
		new_env[j] = ft_strdup((*env)[j]);
		free((*env)[j]);
		j++;
	}
	new_env[j] = ft_strdup(new_entry);
	new_env[j + 1] = NULL;
	free(*env);
	*env = new_env;
}

/**
 * @brief Fonction annexe pour mettre à jour ou initialiser une variable d'environnement dans data->env.
 * @param 1, pointeur sur env   2, la valeur (nom) initiale dans l'env    3, la nouvelle valeur à assigner dans l'env
 * @return void
 */
void	set_env_value(char ***env, const char *var, const char *value)
{
	char	*new_entry;
	size_t	var_len;
	int		i;

	if (!env || !*env || !var || !value)
		return ;
	var_len = ft_strlen(var);
	new_entry = ft_strjoin_3(var, "=", value);
	if (!new_entry)
		return ;
	i = 0;
	while ((*env)[i])
		i++;
	if (!update_env_entry(env, var, new_entry, var_len))
		append_env_entry(env, new_entry, i);
	free(new_entry);
}
