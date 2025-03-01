#include "../minishell.h"

static int wait_piped_pids(pid_t *pids_tab, char **paths, int pid_count)
{
	int	status;
	int	j;

	j = 0;
	status = 0;

	while (j < pid_count)
		waitpid(pids_tab[j++], &status, 0);

	free_string_array(paths);

	// On peut renvoyer le code de retour de la dernière commande
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return status;
}

static void piped_child_routine(int *pipefd, int *fd_in, t_command_table *cmd, t_shell_data *shell_data, char **paths)
{
	char *correct_cmd_path = NULL;

	if (*fd_in != 0)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}

	correct_cmd_path = cmd_is_accessible(cmd->parsed_command[0], paths);
	if (!correct_cmd_path)
	{
		if (ft_strcmp(cmd->token_list->value, ".") == 0)
			ft_putendl_fd(".: filename argument required", 2);
		else if (!cmd->next)
			ft_putendl_fd("Command not found", 2);


		// Libérer les ressources allouées dans le processus enfant avant exit
		free_string_array(paths);
		error_exit(shell_data, NULL, 127);
	}

	execve(correct_cmd_path, cmd->parsed_command, shell_data->env);
	perror("execve");
	exit(EXIT_FAILURE);
}

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

/**
 * @brief Fonction qui gère l'exécution des commandes pipées
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

int execute_piped_commands(t_command_table *cmd, t_shell_data *shell_data)
{
	int		status;
	pid_t	pids[256]; // ok ?
	char	**paths;
	int		child_count;

	status = 0;
	paths = extract_and_split_env_path(shell_data->env);
	if (!paths)
		return (1);
	// Appel de la boucle qui crée les processus enfants et les gère
	child_count = pipes_loop(cmd, shell_data, pids, paths);
	// Attendre tous les processus enfants et récupérer le code de retour de la dernière commande
	status = wait_piped_pids(pids, paths, child_count);
	return (status);
}
