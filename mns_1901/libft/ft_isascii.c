/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:37:39 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:37:42 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
    printf("a is ascii : %d\n", ft_isascii('a'));
    printf("a is ascii : %d\n", isascii('a'));
    printf("0 is ascii : %d\n", ft_isascii('0'));
    printf("0 is ascii : %d\n", isascii('0'));
    printf("# is ascii : %d\n", ft_isascii('#'));
    printf("# is ascii : %d\n", isascii('#'));
    printf("Z is ascii : %d\n", ft_isascii('Z'));
    printf("Z is ascii : %d\n", isascii('Z'));
    printf("\\n is ascii : %d\n", ft_isascii('\n'));
    printf("\\n is ascii : %d\n", isascii('\n'));
}*/
