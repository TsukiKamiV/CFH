#include "../minishell.h"

//char	*allocate_interpreted_string(const char *str)
//{
//	char	*res;
//
//	if (!str)
//		return (NULL);
//	res = malloc(ft_strlen(str) + 1);
//	if (!res)
//		return (NULL);
//	return (res);
//}

//char	handle_escape_char(char c)
//{
//	if (c == 'n')
//		return ('\n');
//	else if (c == 't')
//		return ('\t');
//	else if (c == '\\')
//		return ('\\');
//	else if (c == '\'')
//		return ('\'');
//	else if (c == '\"')
//		return ('\"');
//	return ('\0');
//}

//void	process_backslashes(const char *str, char *res)
//{
//	int	i;
//	int	j;
//	char escaped;
//
//	i = 0;
//	j = 0;
//	while (str[i])
//	{
//		if (str[i] == '\\' && str[i + 1] != '\0')
//		{
//			i++;
//			escaped = handle_escape_char(str[i]);
//			if (escaped != '\0')
//				res[j] = escaped;
//			else
//				res[j] = str[i];
//		}
//		else
//			res[j] = str[i];
//		i++;
//		j++;
//	}
//	res[j] = '\0';
//}

//char	*backslash_interpret(const char *str)
//{
//	char	*res;
//
//	res = allocate_interpreted_string(str);
//	if (!res)
//		return (NULL);
//	process_backslashes(str, res);
//	return (res);
//}

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

//void expand_cmd_token(t_token *tokens, t_shell_data *data)
//{
//	t_token *cur = tokens;
//	char	*tmp;
//
//	while (cur)
//	{
//		if (cur->quote_state != SINGLE_QUOTE)
//		{
//			tmp = perform_expansion(cur->value, data);
//			if (tmp)
//			{
//				free (cur->value);
//				cur->value = tmp;
//			}
//		}
//		//if (cur->quote_state == DOUBLE_QUOTE)
//		//{
//		//	tmp = backslash_interpret(cur->value);
//		//	if (tmp)
//		//	{
//		//		free (cur->value);
//		//		cur->value = tmp;
//		//	}
//		//}
//		//printf("the current token value is: %s\n", cur->value);
//		cur = cur->next;
//	}
//}

/*void expand_cmd_token(t_token *tokens, t_shell_data *data)
{
	t_token *cur = tokens;
	char	*tmp;
	bool	escaped_dollar;
	
	while (cur)
	{
		escaped_dollar = false;
		if (cur->quote_state != SINGLE_QUOTE)
		{
			// Check for `\$` inside double quotes and prevent expansion
			if (cur->quote_state == DOUBLE_QUOTE)
			{
				int i = 0;
				while (cur->value[i])
				{
					// If we find `\$`, mark `escaped_dollar`
					if (cur->value[i] == '\\' && cur->value[i + 1] == '$')
					{
						escaped_dollar = true;
						break;
					}
					i++;
				}
			}
			// Perform expansion only if there is no `\$`
			if (!escaped_dollar)
			{
				tmp = perform_expansion(cur->value, data);
				if (tmp)
				{
					free(cur->value);
					cur->value = tmp;
				}
			}
		}
		cur = cur->next;
	}
}*/
/*void expand_cmd_token(t_token *tokens, t_shell_data *data)
{
	t_token *cur = tokens;
	char	*tmp;
	bool	escaped_dollar;
	
	while (cur)
	{
		escaped_dollar = false;
		
		if (cur->quote_state != SINGLE_QUOTE)
		{
			if (cur->quote_state == DOUBLE_QUOTE)
			{
				int i = 0;
				while (cur->value[i])
				{
					if (cur->value[i] == '\\' && cur->value[i + 1] == '$')
					{
						ft_memmove(&cur->value[i], &cur->value[i + 1], ft_strlen(cur->value) - i);
						escaped_dollar = true;
					}
					i++;
				}
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
		}
		cur = cur->next;
	}
}*/

//void expand_cmd_token(t_token *tokens, t_shell_data *data)
//{
//	t_token *cur = tokens;
//	char	*tmp;
//	bool	escaped_dollar;
//
//	while (cur)
//	{
//		escaped_dollar = false;
//
//		if (cur->quote_state != SINGLE_QUOTE)
//		{
//			if (cur->quote_state == DOUBLE_QUOTE)
//			{
//				int i = 0, j = 0;
//				char *new_value = malloc(ft_strlen(cur->value) + 1);
//				if (!new_value)
//					error_exit(data, "Memory allocation failed", 1);
//
//				while (cur->value[i])
//				{
//					// **处理 `\$`**
//					if (cur->value[i] == '\\' && cur->value[i + 1] == '$')
//					{
//						ft_memmove(&cur->value[i], &cur->value[i + 1], ft_strlen(cur->value) - i);
//						escaped_dollar = true;
//					}
//					// **处理 `\\`, `\'`, `\"`**
//					if (cur->value[i] == '\\' && (cur->value[i + 1] == '\\' || cur->value[i + 1] //== '\"' || cur->value[i + 1] == '\''))
//						i++;  // 跳过第一个 `\`
//					new_value[j++] = cur->value[i++];
//				}
//				new_value[j] = '\0';
//
//				free(cur->value);
//				cur->value = new_value;
//			}
//			// 仅当没有 `\$` 保护时才进行变量扩展
//			if (!escaped_dollar)
//			{
//				tmp = perform_expansion(cur->value, data);
//				if (tmp)
//				{
//					free(cur->value);
//					cur->value = tmp;
//				}
//			}
//		}
//		cur = cur->next;
//	}
//}

void expand_cmd_token(t_token *tokens, t_shell_data *data)
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
						return;
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
}
