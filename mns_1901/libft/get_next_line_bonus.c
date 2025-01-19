/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 21:53:08 by lpantign          #+#    #+#             */
/*   Updated: 2024/12/23 16:10:53 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*next_chars[FD_MAX];

	if (fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = NULL;
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(next_chars[fd]);
		next_chars[fd] = NULL;
		return (NULL);
	}
	line = set_actual_line(fd, next_chars[fd], buffer);
	free(buffer);
	if (!line)
		return (NULL);
	next_chars[fd] = set_next_line(line);
	return (line);
}

char	*set_actual_line(int fd, char *next_chars, char *buffer)
{
	int		read_bytes;
	char	*temp_next_chars;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		else if (read_bytes < 0)
		{
			free(next_chars);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		if (!next_chars)
			next_chars = ft_strdup("");
		temp_next_chars = next_chars;
		next_chars = ft_strjoin(temp_next_chars, buffer);
		free(temp_next_chars);
		temp_next_chars = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (next_chars);
}

char	*set_next_line(char *buffer)
{
	char	*next_chars;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\0')
	{
		next_chars = NULL;
		return (NULL);
	}
	next_chars = ft_substr(buffer, i + 1, ft_strlen(buffer) - i);
	if (!next_chars || next_chars[0] == '\0')
	{
		free(next_chars);
		next_chars = NULL;
	}
	buffer[i + 1] = '\0';
	return (next_chars);
}
