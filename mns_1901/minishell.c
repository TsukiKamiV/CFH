/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:35:50 by lpantign          #+#    #+#             */
/*   Updated: 2025/01/17 09:44:56 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_shell_data	*shell_data;

	shell_data = init_shell_data(env);
	if (!shell_data)
		return (printf("Error when initializing shell_data\n"), 1);
	minishell_mainloop(shell_data);
	rl_clear_history(); // free de l'historique de readline (et non la structure sig_config)
	// if (shell_data)
	// 	free_shell_data(shell_data);
	if (shell_data->env)
		free_string_array(shell_data->env);
	if (shell_data->prompt)
		free(shell_data->prompt);
	if (shell_data->line)
		free(shell_data->line);
	if (shell_data->command_table)
		free_command_table(&shell_data->command_table);
	if (shell_data->tokens)
		free_token_list(shell_data->tokens);
	free(shell_data);

	(void)ac;
	(void)av;
	return (0);
}
