/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:19:06 by luxu              #+#    #+#             */
/*   Updated: 2024/12/28 19:28:18 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	validate_quotes(const char *input)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	while (*input)
	{
		if (*input == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*input == '\"' && !single_quote)
			double_quote = !double_quote;
		input++;
	}
	return !(single_quote || double_quote);
}
