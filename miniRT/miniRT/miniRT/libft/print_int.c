/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:30:23 by luxu              #+#    #+#             */
/*   Updated: 2024/10/06 13:35:10 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_int(int n)
{
	char	*str;
	int		len;

	str = ft_itoa(n);
	len = ft_strlen((const char *)str);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	free (str);
	return (len);
}
