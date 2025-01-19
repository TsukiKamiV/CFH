/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:34:28 by lpantign          #+#    #+#             */
/*   Updated: 2024/06/03 22:35:08 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new_tab;
	int		size;
	int		i;

	i = 0;
	new_tab = NULL;
	size = (int)ft_strlen(src);
	new_tab = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_tab)
		return (NULL);
	while (i <= size)
	{
		new_tab[i] = src[i];
		i++;
	}
	new_tab[size] = '\0';
	return (new_tab);
}
/*
#include <stdio.h>
int main(void)
{
    char    *t = "bonjour test lqlq ^*9";
    char    *dst;

    dst = NULL;
    dst = ft_strdup(t);
    printf("%s\n", dst);
    return (0);
}*/
