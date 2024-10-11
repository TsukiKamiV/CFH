/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:41:49 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 13:35:58 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_unsigned(unsigned int nb)
{
	if (nb > 9)
		ft_put_unsigned(nb / 10);
	if (nb <= 9)
	{
		ft_putchar_fd(nb + '0', 1);
		return ;
	}
	ft_putchar_fd((nb % 10) + '0', 1);
}

int	print_unsigned(unsigned int nb)
{
	unsigned int	i;

	ft_put_unsigned(nb);
	i = 1;
	while (nb > 9)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}
