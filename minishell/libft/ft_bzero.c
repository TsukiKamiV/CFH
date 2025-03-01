/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:17:23 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/23 15:19:42 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char		*ptr;
	size_t				i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
int main(void)
{
    char buffer[10];

    ft_bzero(buffer, sizeof(buffer));

    printf("Test de base : \n");
    if (memcmp(buffer, "\0\0\0\0\0\0\0\0\0\0", 10) == 0)
    {
        printf("Réussi\n");
        printf("Résultat : ");
        for (int i = 0; i < 10; i++)
        {
            printf("%d", buffer[i]);
        }
    }
    else
    {
        printf("Échoué\n");
        printf("Résultat : ");
        for (int i = 0; i < 10; i++) {
            printf("%d", buffer[i]);
        }
    }
}*/
