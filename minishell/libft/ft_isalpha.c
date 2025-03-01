/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:36:13 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:36:44 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
int main(void)
{
    printf("a is alpha : %d\n", ft_isalpha('a'));
    printf("a is alpha : %d\n", isalpha('a'));
    printf("0 is alpha : %d\n", ft_isalpha('0'));
    printf("0 is alpha : %d\n", isalpha('0'));
    printf("# is alpha : %d\n", ft_isalpha('#'));
    printf("# is alpha : %d\n", isalpha('#'));
    printf("Z is alpha : %d\n", ft_isalpha('Z'));
    printf("0 is alpha : %d\n", isalpha('Z'));
}*/
