/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourLogin <yourLogin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:24:41 by yourLogin         #+#    #+#             */
/*   Updated: 2025/01/27 14:24:44 by yourLogin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 *Pour la command echo, le flag -n permet d‘écrire la ligne sans être suivie d'une nouvelle ligne
 *
 */

int	is_n_option(const char *arg)
{
	int	i;
	
	if (arg == NULL)
		return (0);
	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Check les tokens dans shell data, si token value égale à -n, pas de newline, sinon add "\n"
 * A voir si à écrire sur un différent FD_OUT
 */
//int	echo_builtin(t_shell_data *data)
//{
//	t_token	*current;
//	int	newline;
//
//	current = data->command_table->token_list;
//	newline = 1;
//	if (current)
//		current = current->next;
//	if (current && ft_strcmp(current->value, "-n") == 0)
//	{
//		newline = 0;
//		current = current->next;
//	}
//	while (current && current->type == 2)
//	{
//		write(data->command_table->fd_out, current->value, ft_strlen(current->value));
//		if (current->next && current->next->type == 2 && current->next->value[0] != '\0')
//			write(data->command_table->fd_out, " ", 1);
//		current = current->next;
//	}
//	if (newline)
//		write(data->command_table->fd_out, "\n", 1);
//	data->exit_status = 0;
//	return (data->exit_status);
//}


int	echo_builtin(t_shell_data *data)
{
	t_token	*current;
	int		newline;
	
	current = data->command_table->token_list;
	newline = 1;
	if (current)
		current = current->next;
	while (current && is_n_option(current->value))
	{
		newline = 0;
		current = current->next;
	}
	while (current)
	{
		if (current->type == REDIR && !ft_strcmp(current->value, "<"))
		{
			current = current->next;
			if (current)
				current = current->next;
			continue;
		}
		write(data->command_table->fd_out, current->value, ft_strlen(current->value));
		if (current->next && current->next->value[0] != '\0') //à vérifier si l'espace est imprimé correctement
			write(data->command_table->fd_out, " ", 1);
		current = current->next;
	}
	if (newline)
		write(data->command_table->fd_out, "\n", 1);
	data->exit_status = 0;
	return (0);
}
