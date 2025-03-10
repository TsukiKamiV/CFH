#include "../minishell.h"




/**
 * @brief Exécute un processus enfant pour une commande système simple (sans pipe)
 * @param cmd La commande à exécuter
 * @param shell_data La structure principale de minishell
 * @param correct_cmd_path Le chemin correct vers l'exécutable
 * @return Ne retourne rien en cas de succès, exit() en cas d'erreur
 */
// int execute_simple_child(t_command_table *cmd, t_shell_data *shell_data, char *correct_cmd_path)
// {
// 	struct sigaction sa_default;

// 	if (cmd->fd_in == -1)
// 		error_exit(shell_data, "Redirection error: input file", 1);
// 	if (cmd->fd_out == -1)
// 		error_exit(shell_data, "Redirection error: output file", 1);
// 	if (cmd->fd_in != STDIN_FILENO)
// 	{
// 		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
// 		{
// 			perror("dup2 stdin");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(cmd->fd_in);
// 	}
// 	if (cmd->fd_out != STDOUT_FILENO)
// 	{
// 		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2 stdout");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(cmd->fd_out);
// 	}

// 	if (!cmd->parsed_command || !cmd->parsed_command[0])
// 		error_exit(shell_data, "Command not found", 127);

// 	// Rétablir le comportement par défaut des signaux dans l'enfant
// 	sa_default.sa_handler = SIG_DFL;
// 	sa_default.sa_flags = 0;
// 	sigemptyset(&sa_default.sa_mask);
// 	sigaction(SIGINT, &sa_default, NULL);
// 	sigaction(SIGQUIT, &sa_default, NULL);

// 	if (!cmd->parsed_command || !cmd->parsed_command[0] || !shell_data->env)
// 		error_exit(shell_data, "Command not found or env issue", 127);
// 	execve(correct_cmd_path, cmd->parsed_command, shell_data->env);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }
