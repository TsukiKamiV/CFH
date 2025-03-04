/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:29:47 by luxu              #+#    #+#             */
/*   Updated: 2025/01/20 13:49:47 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(t_shell_data *data, const char *msg, int status)
{
	if (!data)
		return ;
	if (msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	data->exit_status = status;
	free_shell_data(data);
	exit (status);
}

void	set_error(t_shell_data *data, const char *msg, int status)
{
	if (!data)
		return ;
	(void) status;
	if (msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd((char *)msg, 2);
		//ft_putstr_fd("\n", 2);
	}
	//data->parse_state = status;
	//free_shell_data(data);
}
