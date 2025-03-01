/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:49:20 by lpantign          #+#    #+#             */
/*   Updated: 2024/05/22 10:52:22 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)ptr;
	while (len > 0)
	{
		*p = (unsigned char)c;
		len--;
		p++;
	}
	return (ptr);
}
/*
int main(void)
{
    // Déclaration d'un tableau de 10 entiers.
    int tab[10];
    
    // Remplissage du tableau avec la valeur 42.
    ft_memset(tab, 10, sizeof(tab));
    
    // Vérification du contenu du tableau.
    for (int i = 0; i < 10; i++) {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    // Déclaration d'une chaîne de caractères.
    char str[10];
    
    // Remplissage de la chaîne avec le caractère 'A'.
    ft_memset(str, 'A', sizeof(str));
    
    // Vérification du contenu de la chaîne.
    printf("%s\n", str);
    return 0;
}*/
