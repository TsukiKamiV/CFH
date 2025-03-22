#include "../minishell.h"

//char *escape_dollar_signs(const char *str)
//{
//	int 	i;
//	int		j;
//	char 	*res;
//
//	if (!str)
//		return (NULL);
//	res = malloc(ft_strlen(str) + 1);
//	if (!res)
//		return (NULL);
//	i = 0;
//	j = 0;
//	while (str[i])
//	{
//		if (str[i] == '\\' && str[i + 1] == '$')
//			i++;
//		res[j++] = str[i++];
//	}
//	res[j] = '\0';
//	return (res);
//}

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

static bool is_token_fully_unquoted_expansion(const char *orig) 
{
	int i = 0;
	while (orig[i]) 
	{
		if (orig[i] == '\'' || orig[i] == '\"')
			return (false);
		if (orig[i] == '$')
		{
			i++;
			if (orig[i] == '?' || ft_isdigit(orig[i]))
			{
				i++;
				continue;
			}
			else if (ft_isalpha(orig[i]) || orig[i] == '_')
			{
				i++;
				while (ft_isalnum(orig[i]) || orig[i] == '_') i++;
			} 
			else
				return (false);
		}
		else
			i++;
	}
	return (true);
}

int	expand_cmd_token(t_token **tokens, t_shell_data *data)
{
	t_token			*cur;
	t_token			*prev;
	char			*orig;
	char			*new_value;
	size_t			orig_len;
	int				i;
	int				j;
	t_quote_state	local_state;
	bool			should_remove;
	
	cur = *tokens;
	prev = NULL;
	while (cur)
	{
		orig = cur->value;
		orig_len = ft_strlen(orig);
		//ici faut re-malloc en bas pour dupliquer env_value
		new_value = malloc(orig_len * 2 + 2048);//leak!!!!!!!!!!!!!!!
		if (!new_value)
			error_exit(data, "Memory allocation failed", 1);
		i = 0;
		j = 0;
		local_state = NO_QUOTE;
		while (orig[i])
		{
			//echo $'hello' doit afficher hello
			if (orig[i] == '$' && local_state == NO_QUOTE && (orig[i + 1] == '\'' || orig[i + 1] == '\"'))
			{
				i++;
				continue;
			}
			//si on entre dans les quotes
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
					i += 2;//si command echo $?hello -> output est 0hello (0 ou autre exit_status)
					continue;
				}
				if (ft_isdigit(orig[i + 1]))
				{
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
						//echo "$"
						new_value[j++] = orig[i++];
						continue;
					}
				}
			}
			//copier tous les caractères non-expanded
			new_value[j++] = orig[i++];
		}
		new_value[j] = '\0';
		//si un token est sans quotes et composé des var expanded sans value, le token ne doit pas être stocké dans la cmd table
		should_remove = (new_value[0] == '\0') && is_token_fully_unquoted_expansion(orig);
		if (should_remove)
		{
			t_token	*next = cur->next;
			free (new_value);
			if (prev)
				prev->next = next;
			else
				*tokens = next;
			free (cur);
			cur = next;
		}
		else
		{
			free (cur->value);
			cur->value = new_value;
			prev = cur;
			cur = cur->next;
		}
	}
	return (0);
}
