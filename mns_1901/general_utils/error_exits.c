/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:29:47 by luxu              #+#    #+#             */
/*   Updated: 2025/01/10 08:34:24 by lpantign         ###   ########.fr       */
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
	/*write a seperate function to free allocated memories*/
	free_shell_data(data);
}
