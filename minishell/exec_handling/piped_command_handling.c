#include "../minishell.h"

void	wait_piped_pids(pid_t *pids_tab, int nb_cmd, t_shell_data *shell_data)
{
	int	status;
	int	j;

	j = 0;
	while (j < nb_cmd)
	{
		waitpid(pids_tab[j], &status, 0);
		if (WIFSIGNALED(status))
		{
			shell_data->exit_status = 128 + WTERMSIG(status); // Gestion correcte du signal reçu
			if (WTERMSIG(status) == SIGQUIT)
				ft_putendl_fd("SIGQUIT: (core dumped)", STDERR_FILENO);
		}
		else if (WIFEXITED(status))
			shell_data->exit_status = WEXITSTATUS(status);
		j++;
	}
}

// Fonction permettant de gérer différentes combinaisons de redirections et de pipes
static void	handle_redir_pipe_context(t_command_table *cmd, int *pipefd)
{
	// Si cmd suivante + pas de redir
	if (cmd->next && cmd->fd_out == STDOUT_FILENO)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	// Si cmd suivante + redir de sortie, priorité à la redir
	else if (cmd->next && cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		// On met à jour le champ fd_out pour pouvoir utiliser echo ou autre ? (vraiment à bien tester ! ça risque de poser problème dans 'autres cas)
		cmd->fd_out = STDOUT_FILENO;
		close(pipefd[0]);
		close(pipefd[1]);
	}
	// Si c'est la dernière commande + redir
	else if (!cmd->next && cmd->fd_out != STDOUT_FILENO)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}

}

// Appelé à chaque fois qu'on passe à la table de commandes suivante (pipe suivant)
static void piped_parent_routine(int *pipefd, int *fd_in, t_command_table *cmd)
{
	if (*fd_in != 0)
		close(*fd_in);

	// Por la prochaine commande, si elle existe, fd_in devient le descripteur de lecture du pipe
	if (cmd->next)
	{
		close(pipefd[1]);
		*fd_in = pipefd[0];
	}
}

// Appelé pour chaque commande séparée par un pipe comme pour le parent
static void piped_child_routine(int *pipefd, int *fd_in, t_command_table *cmd, t_shell_data *shell_data, char **paths)
{
	char *correct_cmd_path = NULL;

	// Remise de SIGINT/SIGQUIT à leur comportement par défaut (desactivé au prealable puis remis une fois le waitpid fini)
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);

	if (!shell_data || !cmd || !cmd->parsed_command || !cmd->parsed_command[0])
	{
		free_string_array(paths);
		error_exit(shell_data, "Invalid command or shell data", 1);
	}

	// Gestion de l'entrée standard depuis le pipe précédent
	if (*fd_in != STDIN_FILENO)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}

	handle_redir_pipe_context(cmd, pipefd);

	// Gestion d'un autre cas de redirection, à voir si nécessaire ? Doublon ??
	if (cmd->fd_in != STDIN_FILENO)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}

	// Exécution d'un builtin
	if (is_builtin(cmd->parsed_command[0]))
	{
		shell_data->exit_status = execute_builtin(cmd, shell_data);
		free_string_array(paths);
		exit(shell_data->exit_status);
	}

	// Traitement d'une commande externe
	correct_cmd_path = cmd_is_accessible(cmd->parsed_command[0], paths);
	if (!correct_cmd_path)
	{
		ft_putendl_fd("Command not found", STDERR_FILENO);
		free_string_array(paths);
		error_exit(shell_data, NULL, 127);
	}

	execve(correct_cmd_path, cmd->parsed_command, shell_data->env);
	perror("execve");
	free_string_array(paths);
	exit(EXIT_FAILURE);
}




/**
 * @brief Fonction centrale qui gère l'exécution des commandes pipées en fonction du processus enfant/parent
 * @param pids Tableau de pid_t qui contiendra les pid des processus enfants
 * @param paths Tableau de chaînes de caractères contenant les chemins d'accès aux commandes
 * @return Le nombre de processus enfants créés
 */
static int pipes_loop(t_command_table *cmd, t_shell_data *shell_data, pid_t *pids, char **paths)
{
	int		fd_in;
	int		i;
	int		pipefd[2];
	pid_t	pid;

	fd_in = 0;
	i = 0;
	while (cmd)
	{
		// Si ce n'est pas la dernière commande, préparer un pipe
		if (cmd->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				free_string_array(paths);
				exit(1);
			}
		}
		// Création du processus pour la commande courante
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free_string_array(paths);
			exit(1);
		}
		else if (pid == 0)  // Processus enfant
			piped_child_routine(pipefd, &fd_in, cmd, shell_data, paths);
		else  // Processus parent
		{
			pids[i++] = pid;
			piped_parent_routine(pipefd, &fd_in, cmd);
		}
		cmd = cmd->next;
	}
	return (i);
}

// Fonction de départ pour l'exécution des commandes avec pipes
int execute_piped_commands(t_command_table *cmd, t_shell_data *shell_data)
{
	pid_t pids[256];
	char **paths;
	int child_count;
	// récupère les signaux SIGINT et SIGQUIT pour les ignorer (trouver pourquoi "incomplete type sigaction is not allowed")
	struct sigaction old_int;
	struct sigaction old_quit;

	ignore_signals_in_parent(&old_int, &old_quit);
	paths = extract_and_split_env_path(shell_data->env);
	if (!paths)
	{
		restore_signals_in_parent(&old_int, &old_quit);
		return (1);
	}
	child_count = pipes_loop(cmd, shell_data, pids, paths);
	wait_piped_pids(pids, child_count, shell_data);
	restore_signals_in_parent(&old_int, &old_quit);
	return (shell_data->exit_status);
}
