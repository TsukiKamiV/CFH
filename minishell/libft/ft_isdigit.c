/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:38:31 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:38:38 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
    printf("a is digit : %d\n", ft_isdigit('a'));
    printf("a is digit : %d\n", isdigit('a'));
    printf("0 is digit : %d\n", ft_isdigit('0'));
    printf("0 is digit : %d\n", isdigit('0'));
    printf("# is digit : %d\n", ft_isdigit('#'));
    printf("# is digit : %d\n", isdigit('#'));
    printf("Z is digit : %d\n", ft_isdigit('Z'));
    printf("Z is digit : %d\n", isdigit('Z'));
}*/
