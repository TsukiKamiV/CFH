#include "../minishell.h"

char *escape_dollar_signs(const char *str)
{
	int 	i;
	int		j;
	char 	*res;
	
	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '$')
			i++;
		res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

/*int expand_cmd_token(t_token *tokens, t_shell_data *data)
{
	t_token *cur = tokens;
	char	*tmp;
	bool	escaped_dollar;
	
	while (cur)
	{
		escaped_dollar = false;
		if (cur->quote_state == SINGLE_QUOTE)
		{
			cur = cur->next;
			continue;
		}
		// **处理 DOUBLE_QUOTE 和 NO_QUOTE**
		if (cur->quote_state == DOUBLE_QUOTE || cur->quote_state == NO_QUOTE)
		{
			int i = 0, j = 0;
			char *new_value = malloc(ft_strlen(cur->value) + 1);
			if (!new_value)
				error_exit(data, "Memory allocation failed", 1);
			
			while (cur->value[i])
			{
				// **处理 DOUBLE_QUOTE 内的 `\$`**
				if (cur->quote_state == DOUBLE_QUOTE && cur->value[i] == '\\' && cur->value[i + 1] == '$')
				{
					ft_memmove(&cur->value[i], &cur->value[i + 1], ft_strlen(cur->value) - i);
					escaped_dollar = true;
					continue;
				}
				// **在 DOUBLE_QUOTE 内，处理 `\\`, `\'`, `\"`**
				if (cur->quote_state == DOUBLE_QUOTE && cur->value[i] == '\\' &&
					(cur->value[i + 1] == '\\' || cur->value[i + 1] == '\"' || cur->value[i + 1] == '\''))
				{
					i++;  // 跳过第一个 `\`
				}
				
				// **在 NO_QUOTE 下，`\` 只影响 `\`, `"`, `'`**
				if (cur->quote_state == NO_QUOTE && cur->value[i] == '\\')
				{
					if (cur->value[i + 1] == '\\' || cur->value[i + 1] == '\'' || cur->value[i + 1] == '\"')
					{
						ft_memmove(&cur->value[i], &cur->value[i + 1], ft_strlen(cur->value) - i);
						//i++;  // 跳过 `\`
					}
					else if (cur->value[i + 1] == '\0')//to handle the command "echo \"
					{
						// **如果 `\` 在行尾，则进入等待输入模式**
						//ft_putstr_fd("> ", 1);
						//fflush(stdout);
						free(new_value);
						return (0);
					}
					else if (cur->value[i] == '\\' && cur->value[i + 1] == '$')
					{
						ft_memmove(&cur->value[i], &cur->value[i + 1], ft_strlen(cur->value) - i);
						escaped_dollar = true;
						continue;
					}
					else
					{
						i++;
						continue;
					}
				}
				new_value[j++] = cur->value[i++];
			}
			new_value[j] = '\0';
			free(cur->value);
			cur->value = new_value;
		}
		if (!escaped_dollar)
		{
			tmp = perform_expansion(cur->value, data);
			if (tmp)
			{
				free(cur->value);
				cur->value = tmp;
			}
		}
		cur = cur->next;
	}
	return (0);
}*/

//int	expand_cmd_token(t_token* tokens, t_shell_data *data)
//{
//	t_token	*cur;
//	char	*orig;
//	char	*new_value;
//	char	*expanded;
//	size_t	orig_len;
//	int		i;
//	int		j;
//	t_quote_state local_state;
//
//	cur = tokens;
//	while (cur)
//	{
//		orig = cur->value;
//		orig_len = ft_strlen(orig);
//		expanded = ft_strdup("");
//		new_value = (char *)malloc(orig_len * 2 + 1);
//		if (!new_value)
//			error_exit(data, "Memory allocation failed", 1);
//		i = 0;
//		j = 0;
//		local_state = NO_QUOTE;
//		while (orig[i])
//		{
//			if (orig[i] == '\'' || orig[i] == '\"')
//			{
//				if (local_state == NO_QUOTE)
//				{
//					if (orig[i] == '\'')
//						local_state = SINGLE_QUOTE;
//					else if (orig[i] == '\"')
//						local_state = DOUBLE_QUOTE;
//				}
//				else if (local_state == SINGLE_QUOTE && orig[i] == '\'')
//					local_state = NO_QUOTE;
//				else if (local_state == DOUBLE_QUOTE && orig[i] == '\"')
//					local_state = NO_QUOTE;
//				new_value[j++] = orig[i++];
//				//i++;
//				continue;
//			}
//			if (orig[i] == '$' && local_state != SINGLE_QUOTE)
//			{
//				int var_start = i + 1;
//				int var_len = 0;
//				while (orig[var_start + var_len] &&
//					   (ft_isalnum(orig[var_start + var_len]) || orig[var_start + //var_len] == '_'))
//				{
//					var_len++;
//				}
//				if (var_len > 0)
//				{
//					char *var_name = ft_substr(orig, var_start, var_len);
//					char *env_value = get_env_value(var_name, data->env);
//					free(var_name);
//					if (env_value)
//					{
//						int k = 0;
//						while (env_value[k])
//							new_value[j++] = env_value[k++];
//					}
//					i = var_start + var_len;
//					continue;
//				}
//				else
//				{
//					/* 如果 '$' 后面没有合法变量名，则将 '$' 原样复制 */
//					new_value[j++] = orig[i++];
//					continue;
//				}
//			}
//			new_value[j++] = orig[i++];
//		}
//		new_value[j] = '\0';
//		free(cur->value);
//		cur->value = new_value;
//		cur = cur->next;
//	}
//	return (0);
//}

int	expand_cmd_token(t_token *tokens, t_shell_data *data)
{
	t_token			*cur;
	char			*orig;
	char			*new_value;
	size_t			orig_len;
	int				i;
	int				j;
	t_quote_state	local_state;
	
	cur = tokens;
	while (cur)
	{
		orig = cur->value;
		orig_len = ft_strlen(orig);
		new_value = malloc(orig_len * 2 + 1);
		if (!new_value)
			error_exit(data, "Memory allocation failed", 1);
		i = 0;
		j = 0;
		local_state = NO_QUOTE;
		while (orig[i])
		{
			if (orig[i] == '$' && (orig[i + 1] == '\'' || orig[i + 1] == '\"'))
			{
				i++;
				continue;
			}
			if (orig[i] == '\'' || orig[i] == '\"')
			{
				if (local_state == NO_QUOTE)
				{
					if (orig[i] == '\'')
						local_state = SINGLE_QUOTE;
					else if (orig[i] == '\"')
						local_state = DOUBLE_QUOTE;
					i++;
					continue;
				}
				else if ((local_state == SINGLE_QUOTE && orig[i] == '\'') ||
						 (local_state == DOUBLE_QUOTE && orig[i] == '\"'))
				{
					local_state = NO_QUOTE;
					i++;
					continue;
				}
				else
				{
					new_value[j++] = orig[i++];
					continue;
				}
			}
			if (orig[i] == '$' && local_state != SINGLE_QUOTE)
			{
				if (orig[i + 1] == '?')
				{
					char *temp;
					int k = 0;
					temp = ft_strdup("");
					temp = handle_exit_status(temp, data);
					while (temp[k])
					{
						new_value[j++] = temp[k];
						k++;
					}
					free(temp);
					i += 2;
					continue;
				}
				else
				{
					int var_start = i + 1;
					int var_len = 0;
					while (orig[var_start + var_len] &&
						   (ft_isalnum(orig[var_start + var_len]) ||
							orig[var_start + var_len] == '_'))
						var_len++;
					if (var_len > 0)
					{
						char *var_name;
						char *env_value;
						int k = 0;
						var_name = ft_substr(orig, var_start, var_len);
						env_value = get_env_value(var_name, data->env);
						free(var_name);
						if (env_value)
						{
							while (env_value[k])
							{
								new_value[j++] = env_value[k];
								k++;
							}
						}
						i = var_start + var_len;
						continue;
					}
					else
					{
						new_value[j++] = orig[i++];
						continue;
					}
				}
			}
			new_value[j++] = orig[i++];
		}
		new_value[j] = '\0';
		free(cur->value);
		cur->value = new_value;
		cur = cur->next;
	}
	return (0);
}
