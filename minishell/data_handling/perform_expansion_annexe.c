#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int to_free)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, len1 + 1);
	ft_strlcat(new_str, s2, len1 + len2 + 1);
	if (to_free == 1 || to_free == 3)
		free(s1);
	if (to_free == 2 || to_free == 3)
		free(s2);
	return (new_str);
}

char	*extract_var_name(const char *str, size_t *start)
{
	size_t	begin;
	char	*var_name;

	begin = *start;
	while (str[*start] && (ft_isalnum(str[*start]) || str[*start] == '_'))
		(*start)++;
	var_name = ft_substr(str, begin, *start - begin);
	return (var_name);
}

void	get_shell_pid(t_shell_data *data)
{
	struct stat sb;
	//int		fd;
	char	*pid_str;

	if (stat("/proc/self", &sb) == -1)
	{
		//ft_putstr_fd("Error: Could not retreive PID\n", STDERR_FILENO);
		ft_strlcpy(data->pid_str, "1", sizeof(data->pid_str));
		return ;
	}
	pid_str = ft_itoa((int)sb.st_ino);
	if (!pid_str)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", STDERR_FILENO);
		return ;
	}
	ft_strlcpy(data->pid_str, pid_str, sizeof(data->pid_str));
	free (pid_str);
}

//char	*expand_variable(char *res, const char *str, size_t *i, t_shell_data *data)
//{
//	char	*var_name;
//
//	if (str[*i + 1] == '?')
//	{
//		(*i)++;
//		return (handle_exit_status(res, data));
//	}
//	else if (str[*i + 1] == '0')
//	{
//		(*i)++;
//		return (ft_strjoin_free(res, data->shell_name, 1));
//	}
//	else if (str[*i + 1] == '$')
//	{
//		(*i)++;
//		return (ft_strjoin_free(res, data->pid_str, 1));
//	}
//	(*i)++;
//	var_name = extract_var_name(str, i);
//	res = handle_env_var(res, var_name, data);
//	free (var_name);
//	return (res);
//}
char	*expand_variable(char *res, const char *str, size_t *i, t_shell_data *data)
{
	char	*var_name;
	//size_t	var_start;
	
	if (!str[*i + 1])
		return (res);
	if (str[*i + 1] == '?')
	{
		(*i) += 2;
		return (handle_exit_status(res, data));
	}
	else if (str[*i + 1] == '0')
	{
		(*i) += 2;
		return (ft_strjoin_free(res, data->shell_name, 1));
	}
	else if (str[*i + 1] == '$')
	{
		(*i) += 2;
		return (ft_strjoin_free(res, data->pid_str, 1));
	}
	(*i)++;
	var_name = extract_var_name(str, i);
	res = handle_env_var(res, var_name, data);
	free (var_name);
	return (res);
}
