/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:46:49 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 15:48:10 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			f(i, s + i);
			i++;
		}
		s[i] = '\0';
	}
}
/*
int main(void)
{
    char *s = "Hello, World!";
    char *new_s = ft_striteri(s, &add_index_to_char);
    printf("%s\n", s);
    printf("%s\n", new_s);
    free(new_s);
    return 0;
}*/
