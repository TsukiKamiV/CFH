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

//bool	validate_quotes(const char *input)
//{
//	bool	single_quote;
//	bool	double_quote;
//
//	single_quote = false;
//	double_quote = false;
//	while (*input)
//	{
//		if (*input == '\'' && !double_quote)
//			single_quote = !single_quote;
//		else if (*input == '\"' && !single_quote)
//			double_quote = !double_quote;
//		input++;
//	}
//	return !(single_quote || double_quote);
//}

bool validate_quotes(const char *cmd)
{
	int i = 0;
	bool in_single_quote = false;
	bool in_double_quote = false;
	
	while (cmd[i])
	{
		if (cmd[i] == '\\' && cmd[i + 1]) // 处理转义字符
		{
			i += 2; // 跳过 `\` 和被转义的字符
			continue;
		}
		
		if (cmd[i] == '\'' && !in_double_quote) // 只有不在双引号内才切换单引号状态
		{
			in_single_quote = !in_single_quote;
		}
		else if (cmd[i] == '"' && !in_single_quote) // 只有不在单引号内才切换双引号状态
		{
			in_double_quote = !in_double_quote;
		}
		
		i++;
	}
	
	// 如果有未关闭的引号，返回 `false`
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
