#include "../minishell.h"


static void	simple_child_routine(t_command_table *cmd, t_shell_data *shell_data)
{
	char	*correct_cmd_path;
	char	**paths;

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
		error_exit(shell_data, "Failed to get paths", 1);
	}
	correct_cmd_path = cmd_is_accessible(cmd->parsed_command[0], paths);
	if (!correct_cmd_path || !cmd->parsed_command[0][0])
	{
		ft_putendl_fd("Command not found", 2);
		error_exit(shell_data, NULL, 127);
	}
	execve(correct_cmd_path, cmd->parsed_command, shell_data->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

// Fonction principale pour les commandes simples sans pipes
int exec_simple_command(t_command_table *cmd, t_shell_data *shell_data)
{
	pid_t pid;
	int status;

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
		simple_child_routine(cmd, shell_data);
	}
	// else parent ???
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
