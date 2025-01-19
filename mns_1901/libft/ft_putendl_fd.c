/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:55:08 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:55:13 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
/*
int main(void)
{
    ft_putendl_fd("STDOUT_FILENO: Hello, World!", 1);
    ft_putendl_fd("STDERR_FILENO: Hello, World!", 2);
    ft_putendl_fd("STDIN_FILENO: Hello, World!", 0);
    ft_putendl_fd("", 1);
    ft_putendl_fd("", 1);
    ft_putendl_fd(NULL, 1); // Seg fault si on vérifie pas si s est NULL
    return 0;
}*/
