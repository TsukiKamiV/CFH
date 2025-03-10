/**
 * @file command_exec.c
 * @brief Contient des fonctions pour exécuter une commande simple ou plusieurs commandes reliées par des pipes
 */

#include "../minishell.h"


// void set_redirection_check(t_command_table *cmd, t_token *current)
// {
// 	if (!ft_strcmp(current->value, ">") || !ft_strcmp(current->value, ">>"))
// 		cmd->check_redir = true;
// }

// void set_pipe_check(t_command_table *cmd, t_token *current)
// {
// 	if (!ft_strcmp(current->value, "|"))
// 		cmd->check_pipe = true;
// }

// int	handle_simple_redir(t_command_table *cmd, t_token *current)
// {
// 	char *err_msg;

// 	if (ft_strcmp(current->value, ">") == 0)
// 	{
// 		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (cmd->fd_out == -1)
// 		{
// 			err_msg = ft_strjoin("Error when opening file for writing: ", current->next->value);
// 			error_exit(NULL, err_msg, 1);
// 		}
// 		cmd->check_redir = true;
// 	}
// 	else if (ft_strcmp(current->value, "<") == 0)
// 	{
// 		cmd->fd_in = open(current->next->value, O_RDONLY);
// 		if (cmd->fd_in == -1)
// 		{
// 			err_msg = ft_strjoin("Error when opening file for reading: ", current->next->value);
// 			error_exit(NULL, err_msg, 1);
// 		}
// 		cmd->check_redir = true;
// 	}
// 	return (0);
// }

// Fonction principale pour les commandes simples sans pipes
int exec_simple_command(t_command_table *cmd, t_shell_data *shell_data)
{
	pid_t pid;
	int status;
	char **paths;
	char *correct_cmd_path;

	struct sigaction old_int;
	struct sigaction old_quit;

	if (!shell_data || !cmd || !cmd->parsed_command || !cmd->parsed_command[0])
		return (1);

	// Builtins sans pipe = process parent
	if (is_builtin(cmd->parsed_command[0]))
	{
		status = execute_builtin(cmd, shell_data);
		shell_data->exit_status = status;
		return status;
	}

	//bouger les signaux du parent pour les enfants
	ignore_signals_in_parent(&old_int, &old_quit);

	// Gestion des commandes systemes dans processus enfant
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		// restauration des signaux par défaut
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->fd_in != STDIN_FILENO)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		if (cmd->fd_out != STDOUT_FILENO)
		{
			dup2(cmd->fd_out, STDOUT_FILENO);
			close(cmd->fd_out);
		}
		paths = extract_and_split_env_path(shell_data->env);
		if (!paths)
		{
			// free_command_table(&shell_data->command_table);
			// free_token_list(shell_data->tokens);
			// free_string_array(shell_data->env);
			// free(shell_data->prompt);
			// free(shell_data->line);
			// free(shell_data);
			error_exit(shell_data, "Failed to get paths", 1);
		}
		correct_cmd_path = cmd_is_accessible(cmd->parsed_command[0], paths);
		if (!correct_cmd_path)
		{
			ft_putendl_fd("Command not found", 2);
			// free_string_array(paths);
			// free_command_table(&shell_data->command_table);
			// free_token_list(shell_data->tokens);
			// free_string_array(shell_data->env);
			// free(shell_data->prompt);
			// free(shell_data->line);
			// free(shell_data);
			error_exit(shell_data, NULL, 127);
		}
		execve(correct_cmd_path, cmd->parsed_command, shell_data->env);
		perror("execve");
		// free_string_array(paths);
		// free_command_table(&shell_data->command_table);
		// free_token_list(shell_data->tokens);
		// free_string_array(shell_data->env);
		// free(shell_data->prompt);
		// free(shell_data->line);
		// free(shell_data);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	restore_signals_in_parent(&old_int, &old_quit);
	if (WIFEXITED(status))
		shell_data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell_data->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("SIGQUIT: (core dumped)", STDERR_FILENO);
	}
	return (shell_data->exit_status);
}
