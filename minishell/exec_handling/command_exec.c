/**
 * @file command_exec.c
 * @brief Contient des fonctions pour exécuter une commande simple ou plusieurs commandes reliées par des pipes
 */

#include "../minishell.h"


// Vérifier et set les redirections
// toujours nécessaire?
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
	char *err_msg;

	if (ft_strcmp(current->value, ">") == 0)
	{
		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd->fd_out == -1)
		{
			err_msg = ft_strjoin("Error when opening file for writing: ", current->next->value);
			error_exit(NULL, err_msg, 1);
		}
		cmd->check_redir = true;
	}
	else if (ft_strcmp(current->value, "<") == 0)
	{
		cmd->fd_in = open(current->next->value, O_RDONLY);
		if (cmd->fd_in == -1)
		{
			err_msg = ft_strjoin("Error when opening file for reading: ", current->next->value);
			error_exit(NULL, err_msg, 1);
		}
		cmd->check_redir = true;
	}
	return (0);
}

// /**
//  * @brief Change le fd de l'output vers un fichier puis restore l'ancien fd de l'output pour continue l'execution
//  * @param cmd La commande à exécuter
//  * @param shell_data La structure principale de minishell
//  * NON UTILISEE
//  */
// int	output_to_file(t_command_table *cmd, t_shell_data *shell_data, int new_fd_out)
// {
// 	int	save_stdout;

// 	save_stdout = cmd->fd_out;
// 	if (dup2(new_fd_out, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2 stdout");
// 		return (1);
// 	}
// 	cmd->fd_out = new_fd_out;
// 	if (cmd->fd_out == -1)
// 	{
// 		cmd->fd_out = save_stdout;
// 		return (1);
// 	}
// 	(void)shell_data;
// 	printf("fd_out = %d\n, fd_in = %d\n, check_redir = %d\n", cmd->fd_out, cmd->fd_in, cmd->check_redir);
// 	return (0);
// }

/**
 * @brief Exécute une commande simple (builtin ou système) en tenant compte des redirections
 * @param cmd La commande à exécuter
 * @param shell_data La structure principale de minishell
 * @return Code de retour de la commande
 */
int	exec_simple_command(t_command_table *cmd, t_shell_data *shell_data)
{
	int		status = 0;
	char	*correct_cmd_path = NULL;  // INITIALISATION

	// Si une erreur de redirection a été détectée (descripteur à -1),
	// on retourne directement 127 sans tenter d'exécuter la commande. Revoir le code de retour ?
	if (cmd->check_redir && ((cmd->fd_in == -1) || (cmd->fd_out == -1)))
		return (127); // a revoir

	if (cmd->token_list->type == BUILTIN)
	{
		status = execute_simple_builtin_command(shell_data);
	}
	else if (cmd->token_list->type == COMMAND)
	{
		// Vérif que la commande est accessible (via le PATH ou autre)
		correct_cmd_path = verify_simple_command(cmd, shell_data);
		if (!correct_cmd_path)
		{
			if (ft_strcmp(cmd->token_list->value, ".") == 0)
				return(ft_putendl_fd(".: filename argument required", 2), 2);
			else if (!getenv("PATH") || !ft_strlen(getenv("PATH")))
				return (ft_putendl_fd("Environnement variable PATH not set", 2), 127);
			else
				return (ft_putendl_fd("Command not found", 2), 127);
		}
		// La fonction execute_system_command utilisera ensuite correct_cmd_path
		// (soit directement, soit par un appel à execute_simple_child())
		status = execute_system_command(cmd, shell_data);
	}
	// Cas particulier pour une cmd débutant par une redir d'entrée
	else if (ft_strcmp(cmd->token_list->value, "<") == 0 && cmd->token_list->type == REDIR)
	{
		if (cmd->token_list->next == NULL)
		{
			ft_putendl_fd("No input after redirection", 2);
			return (127); // a revoir
		}
		status = execute_system_command(cmd, shell_data);
	}
	// else if (ft_strcmp(cmd->token_list->value, "." ) == 0) // Cas ou juste ".", pour ".." c'est command not found return 127
	// {
	// 	if (cmd->token_list->next == NULL)
	// 	{
	// 		ft_putendl_fd("No input after \".\"", 2);
	// 		return (2); // a revoir
	// 	}
	// }
	// Libération du chemin correct s'il a été alloué dans verify_simple_command()
	if (correct_cmd_path)
		free(correct_cmd_path);
	return (status);
}


/*
int exec_simple_command(t_command_table *cmd, t_shell_data *shell_data)
{
	t_token *current = cmd->token_list;

	// Skip over redirections to find the real command
	while (current && (current->type == OPERATOR && ft_strcmp(current->value, "<") == 0))
	{
		//printf("DEBUG: Skipping redirection token: %s\n", current->value);
		current = current->next;
	}
	// If no command is found after redirections, return an error
	if (!current || (current->next && current->next->type != COMMAND))
	{
		printf("ERROR: No command found after redirection\n");
		return (1);
	}
	if (current->next)
		current = current->next;
	// Update the command table's parsed command pointer to the correct command
	cmd->parsed_command = &current->value;
	// Call execute_system_command() with the corrected command
	return (execute_system_command(cmd, shell_data));
}*/
