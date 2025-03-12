/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:53:55 by yourLogin         #+#    #+#             */
/*   Updated: 2025/03/07 13:06:05 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern volatile sig_atomic_t sig_interrupt_flag;


// static void flush_stdin(void)
// {
//     int bytes;
//     char buf[128]; // Taille arbitraire, à vérifier

//     while (1)
//     {
//             bytes = 0;
//             // ioctl() est un appel système qui permet de contrôler oud’interroger un périphérique.
//             // Ici, on l’utilise avec la macro FIONREAD pour savoir combiend’octets sont en attente
//             // sur STDIN (le descripteur de fichier 0). Cette macro remplitla variable "bytes" avec ce nombre.
//             if (ioctl(STDIN_FILENO, FIONREAD, &bytes) == -1)
//                     break;  // En cas d'erreur, on sort de la boucle.
//             if (bytes <= 0)
//                     break;  // S'il n'y a rien à lire, la boucle s'arrête.
//             // On lit alors dans le buffer 'buf' la quantité d'octetsdisponibles (ou 128, le maximum de notre tampon)
//             if (read(STDIN_FILENO, buf, (bytes < 128 ? bytes : 128)) <= 0)
//                     break;  // Si la lecture échoue ou qu'il n'y a plusrien, on sort.
//     }
// }


// static void set_heredoc_signal_handlers(struct sigaction *old_int, struct sigaction *old_quit)
// {
// 	struct sigaction sa_ignore; // handler pour ignorer les signaux
// 	struct sigaction sa_heredoc; // handler pour gérer les signaux dans le cas des heredocs

// 	// Préparation d'un handler custom pour SIGINT (interruption du heredoc)
// 	sa_heredoc.sa_handler = heredoc_sig_handler;
// 	sa_heredoc.sa_flags = 0;
// 	sigemptyset(&sa_heredoc.sa_mask);
// 	// Sauvegarde des anciens handlers avant adaptation
// 	sigaction(SIGINT, NULL, old_int);
// 	sigaction(SIGQUIT, NULL, old_quit);
// 	// adaptation
// 	sigaction(SIGINT, &sa_heredoc, NULL);
// 	// ignore SIGQUIT pour éviter de quitter le shell ou autre problème
// 	sa_ignore.sa_handler = SIG_IGN;
// 	sa_ignore.sa_flags = 0;
// 	sigemptyset(&sa_ignore.sa_mask);
// 	sigaction(SIGQUIT, &sa_ignore, NULL);
// }

// /**
//  * @brief Gère le heredoc en utilisant get_next_line au lieu de readline.
//  *        Le heredoc s'arrête lorsque l'utilisateur entre exactement le délimiteur.
//  *        Le contenu est écrit dans un fichier temporaire ("/tmp/minishell_heredoc"),
//  *        qui est ensuite ouvert en lecture et assigné à cmd->fd_in.
//  */
// void	handle_heredoc(t_command_table *cmd, const char *delimiter)
// {
// 	char *line;
// 	size_t len;
// 	int tmp_fd;
// 	struct sigaction old_sigint;
// 	struct sigaction old_sigquit;

// 	sig_interrupt_flag = 0; // au cas où n'a pas été reset
// 	set_heredoc_signal_handlers(&old_sigint, &old_sigquit);
// 	tmp_fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (tmp_fd == -1)
// 		error_exit(NULL, "Failed to open heredoc temp file.", 1);
// 	while (1)
// 	{
// 		// Flush important quand même ?
// 		if (sig_interrupt_flag)
// 		{
// 			//flush_stdin();
// 			break;
// 		}
// 		if (write(STDOUT_FILENO, "> ", 2) == -1)
// 			error_exit(NULL, "Write error in heredoc prompt.", 1);

// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			break;

// 		len = ft_strlen(line);
// 		if (len > 0 && line[len - 1] == '\n')
// 			line[len - 1] = '\0';

// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}

// 		write(tmp_fd, line, ft_strlen(line));
// 		write(tmp_fd, "\n", 1);
// 		free(line);
// 	}
// 	close(tmp_fd);
// 	sigaction(SIGINT, &old_sigint, NULL);

// 	if (sig_interrupt_flag)
// 	{
// 		unlink("/tmp/minishell_heredoc");
// 		cmd->fd_in = -1;  // Indique une interruption
// 		return ;
// 	}

// 	cmd->fd_in = open("/tmp/minishell_heredoc", O_RDONLY);
// 	if (cmd->fd_in == -1)
// 		error_exit(NULL, "Failed to read heredoc temp file.", 1);

// 	unlink("/tmp/minishell_heredoc");
// }


// Pour l'instant spécifique au cas des heredoc mais clairement à généraliser (voir doublon avec restore_signals_in_parent)
void	restore_shell_signals(t_shell_data *data)
{

	if (!data)
		return ;

	if (data->is_interactive)
	{
		// Remettre la config custom (ex. ignorer SIGQUIT, etc.)
		if (sigaction(SIGINT, &data->sig_config, NULL) == -1)
			perror("sigaction (SIGINT) restore");
		if (sigaction(SIGQUIT, &data->sig_config, NULL) == -1)
			perror("sigaction (SIGQUIT) restore");
	}
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

// Modification du heredoc pour gérer les signaux, fork nécessaire pour les gérer plus proprement
// A tester ++++
static void	handle_heredoc(t_command_table *cmd, const char *delimiter)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		error_exit(NULL, "Failed to create pipe for heredoc.", 1);

	pid = fork();
	if (pid < 0)
		error_exit(NULL, "Failed to fork for heredoc.", 1);

	if (pid == 0) //enfant
	{
		// a bouger dans une fonction à part
		char	*line;
		size_t	len;

		// retablissment signaux
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN); // ign = ignore :))

		// Pas besoin de lecture
		close(pipefd[0]);

		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (!line)  // EOF (Ctrl+D) ou erreur
				break;
			len = ft_strlen(line);
			if (len && line[len - 1] == '\n')
				line[len - 1] = '\0';
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
			free(line);
		}
		close(pipefd[1]);
		exit(0); // Tout s'est bien passé et pas de signaux, gestion d'erreurs à ajouter ?
	}
	else // parent
	{
		close(pipefd[1]);  // Le parent n’écrit pas dans le pipe
		waitpid(pid, &status, 0);
		///////////////////////restore_signals_in_parent?
		// On peut intercepter les signaux qu'on veut ici
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			cmd->fd_in = -1;
			close(pipefd[0]);
			// exit status 130 à rajouter ?
		}
		else
		{
			// pas de signaux ou d'anomalie, on donne a cmd->fd_in le fd de lecture pour le prochain processus ?
			cmd->fd_in = pipefd[0];
		}
	}
}

int	handle_redirection(t_command_table *cmd, t_token *current, t_shell_data *data)
{
	char	*err_msg;

	if (!ft_strcmp(current->value, ">"))
	{
		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd->check_redir = true;
		if (cmd->fd_out == -1)
		{
			err_msg = ft_strjoin(current->next->value, ": no such file or directory");
			if (!err_msg)
				return (-1);
			ft_putendl_fd(err_msg, STDERR_FILENO);
			free(err_msg);
			return (-1);
		}
	}
	else if (!ft_strcmp(current->value, ">>"))
	{
		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd->check_redir = true;
		if (cmd->fd_out == -1)
		{
			err_msg = ft_strjoin(current->next->value, ": no such file or directory");
			if (!err_msg)
				return (-1);
			ft_putendl_fd(err_msg, STDERR_FILENO);
			free(err_msg);
			return (-1);
		}
	}
	else if (!ft_strcmp(current->value, "<"))
	{
		// Au lieu de retourner -1 on affiche juste l'erreur
		// et on remet fd_in à STDIN_FILENO pour la suite des cmds ( echo < nonexist | echo 42 par exemple)
		cmd->fd_in = open(current->next->value, O_RDONLY);
		cmd->check_redir = true;
		if (cmd->fd_in == -1)
		{
			err_msg = ft_strjoin(current->next->value, ": no such file or directory");
			if (err_msg)
			{
				ft_putendl_fd(err_msg, STDERR_FILENO);
				free(err_msg);
			}
			// Pas sûr de ce choix
			cmd->fd_in = STDIN_FILENO;
			return (0);
		}
	}
	else if (!ft_strcmp(current->value, "<<"))
	{
		handle_heredoc(cmd, current->next->value);
		restore_shell_signals(data);
		if (cmd->fd_in == -1)
			return (-1);
	}
	return (0);
}
