/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:45:45 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 13:35:22 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr_len(unsigned long long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_put_ptr(unsigned long long address)
{
	static char	digits[] = "0123456789abcdef";

	if (address >= 16)
		ft_put_ptr(address / 16);
	write(STDOUT_FILENO, &digits[address % 16], 1);
}

int	print_pointer(void *address)
{
	if (address == NULL)
		return (write(STDOUT_FILENO, "(nil)", 5));
	write(STDOUT_FILENO, "0x", 2);
	ft_put_ptr((unsigned long long)address);
	return (ft_ptr_len((unsigned long long)address) + 2);
}
