/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:52:40 by yourLogin         #+#    #+#             */
/*   Updated: 2025/01/06 16:59:58 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//bool	check_double_pipe(char **parsed_command)
//{
//	int	i;
//
//	i = 0;
//	while (parsed_command[i])
//	{
//		if (ft_strcmp(parsed_command[i], "||") == 0)
//			return (true);
//		i++;
//	}
//	return (false);
//}
//
////true: presence de commandes vides   false: pas de commandes vides
//bool	is_empty_cmd(char **parsed_command)
//{
//	int	i;
//
//	//si le tableau entier est vide, true or false??
//	if (parsed_command == NULL)
//		return (true);
//	i = 0;
//	while (parsed_command[i])
//	{
//		if (parsed_command[i][0] == '\0')
//			return (true);
//	}
//	return (false);
//}
//
//bool	cmd_got_pipe(char **parsed_command)
//{
//	int	i;
//
//	i = 0;
//	while (parsed_command[i])
//	{
//		if (ft_strcmp(parsed_command[i], "|") == 0)
//			return (true);
//		i++;
//	}
//	return (false);
//}
