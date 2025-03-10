/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:52:27 by yourLogin         #+#    #+#             */
/*   Updated: 2025/01/06 16:52:30 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool validate_quotes(const char *cmd)
{
	int i = 0;
	bool in_single_quote = false;
	bool in_double_quote = false;
	
	while (cmd[i])
	{
		//if (cmd[i] == '\\' && cmd[i + 1])
		//{
		//	i += 2;
		//	continue;
		//}
		if (cmd[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (cmd[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return !(in_single_quote || in_double_quote);
}

int is_whitespace(char c)
{
	return (c == ' '  || c == '\t' ||
			c == '\n' || c == '\v' ||
			c == '\f' || c == '\r');
}

bool	is_line_empty_or_whitespace(const char *line)
{
	size_t	i;
	
	i = 0;
	
	if (!line)
		return (true);
	while (line[i])
	{
		if (!is_whitespace((unsigned char)line[i]))
			return (false);
		i++;
	}
	return (true);
}
