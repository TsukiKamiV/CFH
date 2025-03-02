#include "../minishell.h"

/**
 * @brief Initialisation de la structure principale de minishell
 * @return La structure principale de minishell allouée et initialisée avec des valeurs par défaut
 */
t_shell_data	*init_shell_data(char **env)
{
	t_shell_data	*shell_data;

	shell_data = malloc(sizeof(t_shell_data));
	if (!shell_data)
		return (NULL);
	shell_data->env = copy_string_array(env);
	shell_data->username = getenv("USER");
	shell_data->is_interactive = 0;
	shell_data->hostname = NULL; // A voir si on peut récupérer le hostname du coup
	shell_data->prompt = ft_strjoin(shell_data->username, "> ");
	shell_data->line = NULL; // Sera actualisé à chaque nouvelle ligne
	shell_data->sig_config = signal_launching();
	if (sigaction(SIGINT, &shell_data->sig_config, NULL) == -1
		|| sigaction(SIGQUIT, &shell_data->sig_config, NULL) == -1)
	{
		perror("sigaction");
		// Autre gestion d'erreur ?
	}
	if (!shell_data->prompt)
		return (NULL);
	shell_data->command_table = NULL;
	shell_data->tokens = NULL;
	shell_data->exit_status = 0;
	shell_data->parse_state = 0;
	get_shell_pid(shell_data);
	return (shell_data);
}

/**
 * @brief Free la structure principale de minishell
 * @param shell_data La structure principale de minishell
 * @todo Free de sig config a faire ?
 */
void	free_shell_data(t_shell_data *shell_data)
{
	if (!shell_data)
		return ;
	free(shell_data->prompt);
	if (shell_data->line)
		free(shell_data->line);
	if (shell_data->command_table)
		free_command_table(&shell_data->command_table);
	if (shell_data->tokens)
		free_token_list(shell_data->tokens);
	if (shell_data->env)
		free_string_array(shell_data->env);
	free(shell_data);
}

char    *get_env_value(const char *var, char **envp)
{
	size_t  var_len;
	int     i;

	if (!var || !*var || !envp)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, var_len) && envp[i][var_len] == '=')
			return (&envp[i][var_len + 1]);
		i++;
	}
	return (NULL);
}
