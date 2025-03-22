#include "../minishell.h"

int is_var_in_list(char **list, const char *key)
{
	int i = 0;

	if (!list || !key)
		return (0);

	while (list[i])
	{
		if (ft_strcmp(list[i], key) == 0)
			return (1);
		i++;
	}
	return (0);
}

char **remove_var_from_list(char **list, const char *key)
{
	int 	i = -1;
	int		j = 0;
	int		len = 0;
	char 	**new_list;

	if (!list || !key)
		return (list);
	while (list[len])
		len++;
	if (len == 0)
		return (list);
	if (!(new_list = malloc(sizeof(char *) * (len + 1))))//leak
		return (list);
	while (list[++i])
	{
		if (ft_strcmp(list[i], key) != 0)
			new_list[j++] = ft_strdup(list[i]);
		free(list[i]);
	}
	new_list[j] = NULL;
	free(list);
	return (new_list);
}

void count_env_and_exported_vars(t_shell_data *data, int *env_size, int *export_size)
{
	*env_size = 0;
	*export_size = 0;

	while (data->env[*env_size])
		(*env_size)++;
	while (data->exported_vars && data->exported_vars[*export_size])
		(*export_size)++;
}

void fill_sorted_exports_env(char **sorted_exports, t_shell_data *data, int env_size)
{
	int i = 0;
	char *equal_pos;
	char *key;
	char *value;
	char	*tmp_str;

	while (i < env_size)
	{
		equal_pos = ft_strchr(data->env[i], '=');
		if (equal_pos)
		{
			key = ft_strndup(data->env[i], equal_pos - data->env[i]);
			value = ft_strdup(equal_pos + 1);
			tmp_str = ft_strjoin("=\"", value);
			free (value);
			value = tmp_str;
			tmp_str = ft_strjoin(value, "\"");
			free(value);
			value = tmp_str;
			tmp_str = ft_strjoin_3("export ", key, value);
			free (key);
			free (value);
			sorted_exports[i] = tmp_str;
		}
		else
			sorted_exports[i] = ft_strjoin("export ", data->env[i]);
		i++;
	}
}

void fill_sorted_exports_exported(char **sorted_exports, t_shell_data *data,
								  int env_size, int export_size)
{
	int j = 0;

	while (j < export_size)
	{
		sorted_exports[env_size + j] =
		ft_strjoin("export ", data->exported_vars[j]);
		j++;
	}
	sorted_exports[env_size + export_size] = NULL;
}
