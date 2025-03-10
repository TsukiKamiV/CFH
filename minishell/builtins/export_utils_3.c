#include "../minishell.h"

void print_sorted_exports(char **sorted_exports, int fd_out)
{
	int i = 0;
	
	sort_char_array(sorted_exports);
	while (sorted_exports[i])
	{
		//printf("%d\n", fd_out);
		ft_putendl_fd(sorted_exports[i], fd_out);
		//ft_putstr_fd(sorted_exports[i], fd_out);
		free(sorted_exports[i]);
		i++;
	}
	free(sorted_exports);
}

int	is_valid_identifier(const char *str)
{
	int	i;
	
	if (!str || !str[0] || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static char	*remove_quotes(const char *str)
{
	size_t	start = 0;
	size_t	end = ft_strlen(str);
	char	first, last;
	char	*result;
	char	*equal_sign;
	
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign || !*(equal_sign + 1))
		return (ft_strdup(str));
	start = (equal_sign - str) + 1;
	end = ft_strlen(str);
	first = str[start];
	last = str[end - 1];
	if ((first == '"' && last == '"') || (first == '\'' && last == '\''))
	{
		start++;
		end--;
	}
	while (start < end && is_whitespace(str[start]))
		start++;
	while (end > start && is_whitespace(str[end - 1]))
		end--;
	result = malloc((equal_sign - str + 1) + (end - start) + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, (equal_sign - str + 2));
	ft_strlcpy(result + (equal_sign - str + 1), str + start, end - start + 1);
	return result;
}

//static char	*trim_whitespace(const char *str)
//{
//	size_t	start;
//	size_t	end;
//
//	start = 0;
//	end = ft_strlen(str);
//	while (start < end && is_whitespace(str[start]))
//		start++;
//	while (end > start && is_whitespace(str[end - 1]))
//		end--;
//	return (ft_substr(str, start, end - start));
//}

static void	collapse_spaces_loop(const char *src, char *dst)
{
	size_t	i;
	size_t	j;
	bool	in_space;
	
	i = 0;
	j = 0;
	in_space = false;
	while (src[i])
	{
		if (is_whitespace(src[i]))
		{
			if (!in_space && j > 0)
				dst[j++] = ' ';
			in_space = true;
		}
		else
		{
			dst[j++] = src[i];
			in_space = false;
		}
		i++;
	}
	dst[j] = '\0';
}

static char	*collapse_spaces(const char *str)
{
	char	*result;
	
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	collapse_spaces_loop(str, result);
	return (result);
}

/**
 * @brief Cette partie enlève les qutoes et les espaces au début et à la fin dans la commande export VAR="   Va   lue   ", laisse un seul espace entre les lettres
 **/

char	*process_new_value(const char *str)
{
	char	*unquoted;
	//char	*trimmed;
	char	*processed;
	
	if (!str)
		return (NULL);
	unquoted = remove_quotes(str);//enlève quotes et espaces au début et à la fin
	if (!unquoted)
		return (NULL);
	//printf("unquoted: %s\n", unquoted);
	//trimmed = trim_whitespace(unquoted);//réduire les espaces au milieu
	//printf("trimmed: %s\n", trimmed);
	//if (!trimmed)
		//return (NULL);
	processed = collapse_spaces(unquoted);
	free(unquoted);
	//printf("processed: %s\n", processed);
	//free(trimmed);
	if (!processed)
		return (NULL);
	if (processed[0] == '\0')
	{
		free(processed);
		return (ft_strdup(""));
	}
	return (processed);
}
