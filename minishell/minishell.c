/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 18:35:50 by lpantign          #+#    #+#             */
/*   Updated: 2025/02/20 21:37:24 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Init les données du shell par défaut/pré initialisées pour un lancement via av
 * @param env, ac, av
 * @return t_shell_data
 */
t_shell_data *init_shell_data_args(char **env)
{
	t_shell_data	*shell_data;

	shell_data = malloc(sizeof(t_shell_data));
	if (!shell_data)
		return (NULL);
	shell_data->env = copy_string_array(env);
	shell_data->username = getenv("USER");
	shell_data->hostname = NULL;
	shell_data->prompt = ft_strjoin(shell_data->username, "> ");
	shell_data->line = NULL;
	shell_data->sig_config = signal_launching();
	if (sigaction(SIGINT, &shell_data->sig_config, NULL) == -1 || sigaction(SIGQUIT, &shell_data->sig_config, NULL) == -1)
		return (printf("Error when calling sigaction\n"), (void)free(shell_data->line), NULL);
	if (!shell_data->prompt)
		return (NULL);
	shell_data->command_table = NULL;
	shell_data->tokens = NULL;
	shell_data->exit_status = 0;
	return (shell_data);
}

static int is_interactive(void)
{
	if (isatty(STDIN_FILENO)) // isatty renvoie 1 si le descripteur de fichier est un terminal (stdin)
		return (1);
	else
		return (0);
}

int	main(int ac, char **av, char **env)
{
	t_shell_data	*shell_data;
	int				status;
	int				i;
	char			*tmp;

	i = 1;
	if (ac > 1)
	{
		shell_data = init_shell_data_args(env);
		if (!shell_data)
			return (printf("Error when initializing shell_data\n"), 1);
		shell_data->is_interactive = is_interactive();
		shell_data->shell_name = av[0];
		while (av[i]) // Copie dans line de av (char ** to char *)
		{
			shell_data->shell_name = av[0];
			if (!shell_data->line)
				shell_data->line = ft_strdup(av[i]);
			else
			{
				tmp = ft_strjoin(shell_data->line, " ");
				if (!tmp)
					return (1);
				free(shell_data->line);
				shell_data->line = ft_strjoin(tmp, av[i]);
				if (!shell_data->line)
					return (1);
				free(tmp);
			}
			i++;
		}
		parse_line(shell_data);
		if (!shell_data->command_table->check_pipe)
			status = exec_simple_command(shell_data->command_table, shell_data);
		else
			status = execute_piped_commands(shell_data->command_table, shell_data);
		free_shell_data(shell_data);
		return (status);
	}
	else
	{
		shell_data = init_shell_data(env);
		if (!shell_data)
			return (printf("Error when initializing shell_data\n"), 1);
		shell_data->is_interactive = is_interactive();
		shell_data->shell_name = av[0];
		//printf("shell name is: %s\n", shell_data->shell_name);
		status = minishell_mainloop(shell_data);
		if (shell_data->is_interactive)
			rl_clear_history(); // free de l'historique de readline (et non la structure sig_config ??)
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
		return (status);
	}
}
