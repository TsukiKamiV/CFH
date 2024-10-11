/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:00:12 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 13:40:49 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*ret;
	char		*current;

	ret = NULL;
	while (fd >= 0)
	{
		current = get_current(fd, &remainder, &ret);
		remainder = NULL;
		if (current == NULL)
			return (ret);
		current = process_current(&current, &ret, &remainder);
		if (current)
			return (current);
	}
	return (NULL);
}

char	*get_current(int fd, char **remainder, char **ret_to_free)
{
	char	*buffer;
	ssize_t	bytes_read;

	if (!*remainder || *remainder[0] == '\0')
	{
		buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0 && ret_to_free)
			{
				free (*ret_to_free);
				*ret_to_free = NULL;
			}
			free (buffer);
			return (NULL);
		}
		*remainder = ft_strdup(buffer);
		free (buffer);
	}
	return (*remainder);
}

char	*process_current(char **current, char **ret, char **remainder_to_fill)
{
	char	*new_line_ptr;

	new_line_ptr = ft_strchr(*current, '\n');
	if (new_line_ptr)
	{
		*new_line_ptr = '\0';
		if (BUFFER_SIZE != 1 || *current[0] == '\n')
		{
			*remainder_to_fill = ft_strdup(new_line_ptr + 1);
			if (*remainder_to_fill && *remainder_to_fill[0] == '\0')
			{
				free (*remainder_to_fill);
				*remainder_to_fill = NULL;
			}
		}
		*ret = add_break(add(*ret, *current));
		return (*ret);
	}
	else
		*ret = add(*ret, *current);
	return (NULL);
}

char	*add(char *a, char *b)
{
	char	*temp;

	if (!a)
		temp = ft_strdup(b);
	else
	{
		temp = ft_strjoin(a, b);
		free (a);
	}
	free (b);
	return (temp);
}

char	*add_break(char *a)
{
	char	*temp;

	if (!a)
		temp = "\n";
	else
	{
		temp = ft_strjoin(a, "\n");
		free (a);
	}
	return (temp);
}
