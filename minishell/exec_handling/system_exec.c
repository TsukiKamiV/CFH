#include "../minishell.h"

// int execute_system_command(t_command_table *cmd, t_shell_data *shell_data)
// {
// 	pid_t pid;
// 	char *correct_cmd_path;
// 	char **env_paths;
// 	int status = 0;
// 	struct sigaction old_sigint, old_sigquit;
// 	struct sigaction sa_default;

// 	if (!cmd || !cmd->parsed_command || !shell_data || !cmd->token_list)
// 		return (-1);

// 	env_paths = extract_and_split_env_path(shell_data->env);
// 	if (!env_paths)
// 		return (-1);

// 	if (check_env_var("PATH", shell_data->env) == 0)
// 	{
// 		free_string_array(env_paths);
// 		return (-1); // PATH inexistant
// 	}

// 	correct_cmd_path = cmd_is_accessible(cmd->parsed_command[0], env_paths);
// 	if (!correct_cmd_path)
// 	{
// 		free_string_array(env_paths);
// 		return (-1);
// 	}

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		free_string_array(env_paths);
// 		free(correct_cmd_path);
// 		return (-1);
// 	}
// 	else if (pid == 0) // Processus enfant
// 	{
// 		// Rétablir les signaux par défaut dans l'enfant
// 		sa_default.sa_handler = SIG_DFL;
// 		sa_default.sa_flags = 0;
// 		sigemptyset(&sa_default.sa_mask);
// 		sigaction(SIGINT, &sa_default, NULL);
// 		sigaction(SIGQUIT, &sa_default, NULL);

// 		// Gestion des redirections et exécution de la commande
// 		// if (cmd->check_redir)
// 		execute_simple_child(cmd, shell_data, correct_cmd_path);
// 		// else
// 		// 	execute_simple_child(cmd, shell_data, correct_cmd_path);
// 		// On ne devrait jamais atteindre ce point
// 		exit(EXIT_FAILURE);
// 	}
// 	else // Processus parent
// 	{
// 		// Ignorer SIGINT et SIGQUIT pendant le wait
// 		ignore_signals_in_parent(&old_sigint, &old_sigquit);

// 		waitpid(pid, &status, 0);

// 		// Restaurer les handlers initiaux
// 		restore_signals_in_parent(&old_sigint, &old_sigquit);

// 		free_string_array(env_paths);
// 		free(correct_cmd_path);

// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 		else if (WIFSIGNALED(status))
// 			return (128 + WTERMSIG(status)); // Ex : 130 pour SIGINT
// 	}
// 	return (-1); // On ne devrait jamais atteindre ce point
// }
