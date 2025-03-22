#include "../minishell.h"

int handle_export_no_arguments(t_shell_data *data)
{
	int env_size;
	int	export_size;
	int	total_size;
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
	char	*equal_pos;
	char	*clean_entry;
	char	**tmp_env;
	char	**tmp_exp_vars;
	
	equal_pos = ft_strnstr(new_entry, "+=", ft_strlen(new_entry));
	if (equal_pos)
		clean_entry = ft_strjoin(key, equal_pos + 1);
	else
		clean_entry = ft_strdup(new_entry);
	if (index >= 0)
		tmp_env = modify_string_in_array(data->env, clean_entry, index);
	else
	{
		tmp_env = add_string_to_array(data->env, clean_entry);//leak
		free_string_array(data->env);
	}
	free (clean_entry);
	data->env = tmp_env;
	tmp_exp_vars = remove_var_from_list(data->exported_vars, key);
	data->exported_vars = tmp_exp_vars;
}

void handle_export_without_value(t_shell_data *data, char *key)
{
	char	**tmp_tab;
	
	if (!is_var_in_list(data->exported_vars, key))
	{
		tmp_tab = add_string_to_array(data->exported_vars, key);
		free_string_array(data->exported_vars);
		data->exported_vars = tmp_tab;
	}
}

//void process_export_variable(t_shell_data *data, t_token *token)
//{
//	char *new_entry;
//	char *key;
//	int index;
//	int has_equal;
//	int	has_plus;
//
//	while (token)
//	{
//		has_equal = (ft_strchr(token->value, '=') != NULL);
//		has_plus = (ft_strnstr(token->value, "+=", ft_strlen(token->value)) != NULL);
//		new_entry = process_new_value(token->value);
//		key = extract_key(new_entry);
//		index = get_env_index(data->env, key);
//		if (index > 0 && !has_equal)
//		{
//			free (new_entry);
//			free (key);
//			token = token->next;
//			continue;
//		}
//		if (has_plus)
//		{
//			if (index >= 0)
//				data->env = append_string_in_array(data->env, key, ft_strchr(new_entry, //'=') + 1);
//			else
//				handle_export_with_value(data, key, new_entry, index);
//		}
//		else if (has_equal)
//			handle_export_with_value(data, key, new_entry, index);
//		else
//			handle_export_without_value(data, key);
//		free(new_entry);
//		free(key);
//		token = token->next;
//	}
//}

static int can_skip_token(int index, int has_equal, char *new_entry, char *key)
{
	if (index > 0 && !has_equal)
	{
		free(new_entry);
		free(key);
		return (1);
	}
	return (0);
}

static void export_value(t_shell_data *data, int has_plus, int index, char *key, char *new_entry)
{
	if (has_plus)
	{
		if (index >= 0)
			data->env = append_string_in_array(data->env, key,
											   ft_strchr(new_entry, '=') + 1);
		else
			handle_export_with_value(data, key, new_entry, index);
	}
	else if (ft_strchr(new_entry, '=') != NULL)
		handle_export_with_value(data, key, new_entry, index);
	else
		handle_export_without_value(data, key);
}

void process_export_variable(t_shell_data *data, t_token *token)
{
	char *new_entry;
	char *key;
	int  index;
	int  has_equal;
	int  has_plus;
	
	while (token)
	{
		has_equal = (ft_strchr(token->value, '=') != NULL);
		has_plus = (ft_strnstr(token->value, "+=", ft_strlen(token->value)) != NULL);
		new_entry = process_new_value(token->value);
		key = extract_key(new_entry);
		index = get_env_index(data->env, key);
		if (can_skip_token(index, has_equal, new_entry, key))
		{
			token = token->next;
			continue;
		}
		export_value(data, has_plus, index, key, new_entry);
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

