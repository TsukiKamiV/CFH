/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:48:43 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 13:34:56 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_hex_digits(unsigned int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static void	ft_put_hex(unsigned int n, const int fmt)
{
	static char	upper_case[] = "0123456789ABCDEF";
	static char	lower_case[] = "0123456789abcdef";

	if (n >= 16)
		ft_put_hex((n / 16), fmt);
	if (fmt == 55)
		write(STDOUT_FILENO, &upper_case[n % 16], 1);
	else if (fmt == 87)
		write(STDOUT_FILENO, &lower_case[n % 16], 1);
}

int	print_hex(unsigned int n, const int fmt)
{
	ft_put_hex(n, fmt);
	return (count_hex_digits(n));
}
