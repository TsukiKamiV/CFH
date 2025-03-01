/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:02:21 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 11:02:30 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
/*
int main(void)
{
    ft_putstr_fd("STDOUT_FILENO: Hello, World!\n", 1);
    ft_putstr_fd("STDERR_FILENO: Hello, World!\n", 2);
    ft_putstr_fd("STDIN_FILENO: Hello, World!\n", 0);
    ft_putstr_fd("", 1);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd(NULL, 1); // Seg fault si on vérifie pas si s est NULL
    return 0;
}*/
