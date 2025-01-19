/**
 * @file command_exec.c
 * @brief Contient des fonctions pour exécuter une commande simple, sans pipes.asm
 *
 */

#include "../minishell.h"


/**
 * @brief Execute une commande système sans pipe
 * @param cmd La commande à exécuter
 * @param shell_data La structure principale de minishell
 * @return 0 si la commande a été exécutée, -1 si la commande n'a pas été trouvée
 */
int	execute_system_command(t_command_table *cmd, t_shell_data *shell_data)
{
	(void)shell_data;
	(void)cmd;
	printf("Commande système en cours de création\n");
	return (0);
}

/**
 * @brief Vérifie une commande simple sans pipe et retourne 1 si elle est valide (builtins ou cmd système), 0 sinon
 * @param cmd La commande à vérifier
 * @param shell_data La structure principale de minishell
 * @return 1 si la commande est valide, 0 sinon
 */
int	verify_simple_command(t_command_table *cmd, t_shell_data *shell_data)
{
	int		i;
	char	**cmd_paths;

	if (!cmd->token_list || !shell_data)
		return (0);
	if (cmd->token_list->type != COMMAND && cmd->token_list->type != BUILTIN)
		return (0);
	i = 0;
	if (cmd->token_list->type == BUILTIN)
		return (1);
	else if (cmd->token_list->type == COMMAND)
	{
		cmd_paths = extract_and_split_env_path(shell_data->env);
		if (!cmd_paths)
			return (0);
		while (cmd_paths[i])
		{
			if (cmd_is_accessible(cmd->parsed_command[0], cmd_paths))
			{
				free_string_array(cmd_paths);
				return (1);
			}
			i++;
		}
		free_string_array(cmd_paths);
	}
	return (0);
}


/**
 * @brief Exécute une commande simple sans pipe
 *
 * @param cmd La commande à exécuter
 * @param shell_data La structure principale de minishell
 */
int	exec_simple_command(t_command_table *cmd, t_shell_data *shell_data)
{
	int	status = 0;

	if (cmd->token_list->type == BUILTIN)
			status = execute_builtin_command(shell_data);
	else if (cmd->token_list->type == COMMAND)
	{
		if (verify_simple_command(cmd, shell_data) == 1)
		{
			status = execute_system_command(cmd, shell_data);
		}
		else if (verify_simple_command(cmd, shell_data) == 0)
			printf("Invalid command: %s\n", cmd->parsed_command[0]);
	}
	else
		printf("Command not found: %s\n", cmd->parsed_command[0]);
	return (status);
}

void set_redirection_check(t_command_table *cmd, t_token *current)
{
	if (!ft_strcmp(current->value, ">") || !ft_strcmp(current->value, ">>"))
		cmd->check_redir = true;
}

void set_pipe_check(t_command_table *cmd, t_token *current)
{
	if (!ft_strcmp(current->value, "|"))
		cmd->check_pipe = true;
}

int	handle_simple_redir(t_command_table *cmd, t_token *current)
{
	if (ft_strcmp(current->value, ">") == 0)
	{
		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
			return (printf("Error when opening file for writing\n"), 1);
		cmd->check_redir = true;
	}
	else if (ft_strcmp(current->value, "<") == 0)
	{
		cmd->fd_in = open(current->next->value, O_RDONLY);
		if (cmd->fd_in == -1)
			return (printf("Error when opening file for reading\n"), 1);
		cmd->check_redir = true;
	}
	return (0);
	// Cf redir_and_heredoc.c pour >>
	// à close
}

