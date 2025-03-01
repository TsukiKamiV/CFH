/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:34:40 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:35:29 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
    printf("a is alpha : %d\n", ft_isalnum('a'));
    printf("a is alpha : %d\n", isalnum('a'));
    printf("0 is alpha : %d\n", ft_isalnum('0'));
    printf("0 is alpha : %d\n", isalnum('0'));
    printf("# is alpha : %d\n", ft_isalnum('#'));
    printf("# is alpha : %d\n", isalnum('#'));
    printf("Z is alpha : %d\n", ft_isalnum('Z'));
    printf("Z is alpha : %d\n", isalnum('Z'));
}*/
