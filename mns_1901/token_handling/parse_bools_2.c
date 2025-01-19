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

bool check_open_quote(char **parsed_command) 
{
    bool single_quote = false;
    bool double_quote = false;

    while (*parsed_command) 
    {
        const char *input = *parsed_command;

        while (*input) 
        {
            if (*input == '\'' && !double_quote) 
                single_quote = !single_quote;
            else if (*input == '\"' && !single_quote) 
                double_quote = !double_quote;
            input++;
        }
        parsed_command++;
    }
    return !(single_quote || double_quote);
}
