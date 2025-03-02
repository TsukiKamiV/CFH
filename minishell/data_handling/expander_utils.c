#include "../minishell.h"

/** Pour traiter le $?
 * @param res - string en cours d'expansion; data
 * @return string + code de sortie 
 */
char    *handle_exit_status(char *res, t_shell_data *data)
{
    char    *exit_status;
    char    *tmp;

	if (data->parse_state != 0)
		exit_status = ft_itoa(data->parse_state);
	else
    	exit_status = ft_itoa(data->exit_status);
    tmp = append_str(res, exit_status);
    free (exit_status);
    return (tmp);
}

char    *append_str(char *res, const char *str)
{
    char    *tmp;

    if (!str)
	    return (res);
    tmp = ft_strjoin(res, str);
    if (res)
    	free (res);
    return (tmp);
}

char    *append_substr(char *res, const char *src, size_t begin, size_t len)
{
    char    *substr;
    char    *tmp;

    substr = ft_substr(src, begin, len);
    tmp = append_str(res, substr);
    free (substr);
    return (tmp);
}

/**
 * @param res - 
 */
char    *handle_env_var(char *res, const char *var_name, t_shell_data *data)
{
    char    *env_value;

    env_value = get_env_value(var_name, data->env);
    if (!env_value)
        env_value = "";
    return (append_str(res, env_value));
}

/** Si présence de $ dans la commande, gérer l'expansion
 * @param current_token->value, data
 * @return pointeur au résultat après l'expansion
 */
//char    *perform_expansion(const char *str, t_shell_data *data)
//{
//    char    *res;
//    char    *var_name;
//    size_t  i;
//    size_t  start;
//
//    res = ft_strdup("");
//    i = 0;
//    while (str[i])
//    {
//        if ((int)str[i] == '$')
//        {
//            if ((int)str[i + 1] == '?')
//                res = handle_exit_status(res, data);
//            else
//            {
//                start = ++i;
//                while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
//                    i++;
//                var_name = ft_substr(str, start, i - start);
//                res = handle_env_var(res, var_name, data);
//                free (var_name);
//            }
//			i = i + ft_strlen(str);
//        }
//        else
//        {
//            start = i;
//            while (str[i] && str[i] != '$')
//                i++;
//            res = append_substr(res, str, start, i - start);
//        }
//    }
//    return (res);
//}

/*char	*perform_expansion(const char *str, t_shell_data *data)
{
	char	*res;
	size_t	i;
	size_t	start;
	
	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			res = expand_variable(res, str, &i, data);
			return (res);
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
			{
				printf("%c\n", str[i]);
				i++;
			}
			return (append_substr(res, str, start, i - start));
		}
	}
	return (NULL);
}*/
//char	*perform_expansion(const char *str, t_shell_data *data)
//{
//	char	*res;
//	size_t	i;
//	size_t	start;
//
//	if (!str)
//		return (NULL);
//	res = ft_strdup(""); // Start with an empty result
//	i = 0;
//	while (str[i]) // Process the entire string
//	{
//		if (str[i] == '$') // If we detect an env variable
//			res = expand_variable(res, str, &i, data); // Expand it
//		else // If it's normal text, append it to the result
//		{
//			start = i;
//			while (str[i] && str[i] != '$') // Collect text before the next '$'
//				i++;
//			res = append_substr(res, str, start, i - start); // Append text
//		}
//	}
//	return (res);
//}

char	*perform_expansion(const char *str, t_shell_data *data)
{
	char	*res;
	char	*next_dollar;
	size_t	start;
	size_t	local_start;
	
	if (!str)
		return (NULL);
	res = ft_strdup("");
	while (*str)
	{
		next_dollar = ft_strchr(str, '$');
		if (!next_dollar)
		{
			res = append_str(res, str);
			break;
		}
		start = next_dollar - str;
		if (start > 0)
			res = append_substr(res, str, 0, start);
		str = next_dollar;
		if ((*(str + 1) && ft_strchr("=-!#^%&*()[]{}.,:", *(str + 1))) || !(*(str + 1)))
		{
			start = 1;
			while (str[start] && !is_whitespace(str[start]))
				start++;
			res = append_substr(res, str, 0, start);
			str += start;
		}
		else
		{
			local_start = 0;
			res = expand_variable(res, str, &local_start, data);
			str += local_start;
		}
	}
	return (res);
}
