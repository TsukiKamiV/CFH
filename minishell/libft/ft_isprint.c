/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:39:36 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:39:39 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
    printf("a is printable : %d\n", ft_isprint('a'));
    printf("a is printable : %d\n", isprint('a'));
    printf("0 is printable : %d\n", ft_isprint('0'));
    printf("0 is printable : %d\n", isprint('0'));
    printf("# is printable : %d\n", ft_isprint('#'));
    printf("# is printable : %d\n", isprint('#'));
    printf("Z is printable : %d\n", ft_isprint('Z'));
    printf("Z is printable : %d\n", isprint('Z'));
    printf("\\n is printable : %d\n", ft_isprint('\n'));
    printf("\\n is printable : %d\n", isprint('\n'));
}*/
