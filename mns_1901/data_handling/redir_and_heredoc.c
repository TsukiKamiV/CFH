/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_and_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:53:55 by yourLogin         #+#    #+#             */
/*   Updated: 2025/01/15 09:45:26 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_heredoc(t_command_table *cmd, const char *delimiter)
{
	char	*line;
	int		tmp_fd;

	tmp_fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
		error_exit(NULL, "Failed to open heredoc temp file.", 1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break;
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free (line);
	}
	free (line);
	close (tmp_fd);
	cmd->fd_in = open("/tmp/minishell_heredoc", O_RDONLY);
	if (cmd->fd_in == -1)
		error_exit(NULL, "Failed to read heredoc temp file.", 1);
}

void handle_redirection(t_command_table *cmd, t_token *current)
{
	char    *err_msg;

	if (!ft_strcmp(current->value, ">")) // 
		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(current->value, ">>"))
		cmd->fd_out = open(current->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(current->value, "<"))
		cmd->fd_in = open(current->next->value, O_RDONLY);
	else if (!ft_strcmp(current->value, "<<"))
		handle_heredoc(cmd, current->next->value);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		err_msg = ft_strjoin("Redirection error: ", current->next->value);
		if (!err_msg)
			error_exit(NULL, "Memory allocation failed when generating error message.", 1);
		error_exit(NULL, err_msg, 1);
	}
}
