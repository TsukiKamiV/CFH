/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:59:23 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 11:01:11 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar_fd('-', fd);
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}
/*
int main(void)
{
    ft_putnbr_fd(1, 1);
    printf("\n");
    ft_putnbr_fd(1, 2);
    printf("\n");
    ft_putnbr_fd(2147483647, 1);
    printf("\n");
    ft_putnbr_fd(2147483647, 2);
    printf("\n");
    ft_putnbr_fd(2147483647, 3); // ?
    printf("\n");
    ft_putnbr_fd(0, 0);
    printf("\n");
    ft_putnbr_fd(0, 1);
    printf("\n");
    ft_putnbr_fd(-2147483648, 1);
    return 0;
}*/
