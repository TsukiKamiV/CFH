/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:23:58 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 13:36:16 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_format(const char s, va_list ap)
{
	int	i;

	i = 0;
	if (s == 'c')
		i = print_char((char)va_arg(ap, int));
	else if (s == 's')
		i = print_string(va_arg(ap, char *));
	else if (s == 'p')
		i = print_pointer(va_arg(ap, void *));
	else if (s == 'd' || s == 'i')
		i = print_int(va_arg(ap, int));
	else if (s == 'u')
		i = print_unsigned(va_arg(ap, unsigned int));
	else if (s == 'x')
		i = print_hex(va_arg(ap, unsigned int), 87);
	else if (s == 'X')
		i = print_hex(va_arg(ap, unsigned int), 55);
	else if (s == '%')
		i = print_char('%');
	return (i);
}

int	ft_printf(const char *arg, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, arg);
	count = 0;
	while (*arg)
	{
		if (*arg == '%')
			count += print_format(*(++arg), ap);
		else
			count += write(1, arg, 1);
		++arg;
	}
	va_end(ap);
	return (count);
}
