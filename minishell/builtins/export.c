#include "../minishell.h"
//int export_builtin(t_shell_data *data)
//{
//	t_token *token = data->command_table->token_list->next;
//	int	i;
//	int	j;
//	int	env_size;
//	int	export_size;
//	int	total_size;
//	char	**sorted_exports;
//	char	*equal_pos;
//	char	*key;
//	char	*value;
//
//	env_size = 0;
//	export_size = 0;
//	i = 0;
//	j = 0;
//	if (!token)
//	{
//		while (data->env[env_size])
//			env_size++;
//		while (data->exported_vars && data->exported_vars[export_size])
//			export_size++;
//		total_size = env_size + export_size;
//		sorted_exports = malloc(sizeof(char *) * (total_size + 1));
//		if (!sorted_exports)
//			return (1);
//		while (i < env_size)
//		{
//			equal_pos = ft_strchr(data->env[i], '=');
//			if (equal_pos)
//			{
//				key = ft_strndup(data->env[i], equal_pos - data->env[i]);
//				value = ft_strdup(equal_pos + 1);
//				sorted_exports[i] = ft_strjoin_3("declare -x ", key, ft_strjoin("=\"", ft_strjoin(value, "\"")));
//				free(key);
//				free(value);
//			}
//			else
//				sorted_exports[i] = ft_strjoin("declare -x ", data->env[i]);
//			i++;
//		}
//		while (j < export_size)
//		{
//			sorted_exports[env_size + j] = ft_strjoin("declare -x ", data->exported_vars[j]);
//			j++;
//		}
//		sorted_exports[total_size] = NULL;
//		sort_char_array(sorted_exports);
//		i = 0;
//		while (sorted_exports[i])
//		{
//			ft_putendl_fd(sorted_exports[i], data->command_table->fd_out);
//			free(sorted_exports[i]);
//			i++;
//		}
//		free(sorted_exports);
//		data->exit_status = 0;
//		return (data->exit_status);
//	}
//		/*int i = 0;
//		while (data->env[i])
//		{
//			equal_pos = ft_strchr(data->env[i], '=');
//			if (equal_pos)
//			{
//				key = ft_strndup(data->env[i], equal_pos - data->env[i]);
//				value = ft_strdup(equal_pos + 1);
//				output = ft_strjoin_3("declare -x ", key, ft_strjoin("=\"", ft_strjoin(value, "\"")));
//				free(key);
//				free(value);
//			}
//			else
//				output = ft_strjoin("declare -x ", data->env[i]);
//			ft_putendl_fd(output, data->command_table->fd_out);
//			free(output);
//			i++;
//		}
//		i = 0;
//		while (data->exported_vars && data->exported_vars[i])
//		{
//			output = ft_strjoin("declare -x ", data->exported_vars[i]);
//			ft_putendl_fd(output, data->command_table->fd_out);
//			free (output);
//			i++;
//		}
//		data->exit_status = 0;
//		return (data->exit_status);*/
//	else
//	{
//		char	*new_entry;
//		char	*key;
//		int		index;
//		int		has_equal;
//
//		while (token)
//		{
//			if (ft_strchr(token->value, '=') != NULL)
//				has_equal = 1;
//			else
//				has_equal = 0;
//			new_entry = ft_strdup(token->value);
//			key = extract_key(new_entry);
//			index = get_env_index(data->env, key);
//			if (has_equal)
//			{
//				if (index >= 0)
//					data->env = modify_string_in_array(data->env, new_entry, index);
//				else
//					data->env = add_string_to_array(data->env, new_entry);
//				data->exported_vars = remove_var_from_list(data->exported_vars, key);
//			}
//			else
//			{
//				if (!is_var_in_list(data->exported_vars, key))
//					data->exported_vars = add_string_to_array(data->exported_vars, key);
//			}
//			free (new_entry);
//			free (key);
//			token = token->next;
//		}
//		data->exit_status = 0;
//		return (data->exit_status);
//	}
//}

int handle_export_no_arguments(t_shell_data *data)
{
	int env_size, export_size, total_size;
	char **sorted_exports;

	count_env_and_exported_vars(data, &env_size, &export_size);
	total_size = env_size + export_size;
	sorted_exports = malloc(sizeof(char *) * (total_size + 1));
	if (!sorted_exports)
		return (1);
	fill_sorted_exports_env(sorted_exports, data, env_size);
	fill_sorted_exports_exported(sorted_exports, data, env_size, export_size);
	print_sorted_exports(sorted_exports, data->command_table->fd_out);
	data->exit_status = 0;
	return (data->exit_status);
}

void handle_export_with_value(t_shell_data *data, char *key, char *new_entry, int index)
{
	if (index >= 0)
		data->env = modify_string_in_array(data->env, new_entry, index);
	else
		data->env = add_string_to_array(data->env, new_entry);
	data->exported_vars = remove_var_from_list(data->exported_vars, key);
}

void handle_export_without_value(t_shell_data *data, char *key)
{
	if (!is_var_in_list(data->exported_vars, key))
		data->exported_vars = add_string_to_array(data->exported_vars, key);
}

void process_export_variable(t_shell_data *data, t_token *token)
{
	char *new_entry;
	char *key;
	int index;
	int has_equal;

	while (token)
	{
		has_equal = (ft_strchr(token->value, '=') != NULL);
		new_entry = ft_strdup(token->value);
		key = extract_key(new_entry);
		index = get_env_index(data->env, key);
		if (has_equal)
			handle_export_with_value(data, key, new_entry, index);
		else
			handle_export_without_value(data, key);
		free(new_entry);
		free(key);
		token = token->next;
	}
}

int export_builtin(t_shell_data *data)
{
	t_token *token;
	char	*key;

	token = data->command_table->token_list->next;
	if (!token || token->type == REDIR || token->type == PIPE)
		return handle_export_no_arguments(data);
	while (token)
	{
		key = extract_key(token->value);
		if (!is_valid_identifier(key) && token->type != REDIR && token->type != PIPE)
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(token->value, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			free (key);
			data->exit_status = 1;
			return (1);
		}
		free (key);
		token = token->next;
	}
	process_export_variable(data, data->command_table->token_list->next);
	data->exit_status = 0;
	return (data->exit_status);
}
