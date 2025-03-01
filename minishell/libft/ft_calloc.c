/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:27:48 by lpantign          #+#    #+#             */
/*   Updated: 2024/06/04 01:31:22 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*
int	main(void)
{
    char *str;
    char *str2;
    int i;
    i = 0;
    str = ft_calloc(10, sizeof(char));
    str2 = calloc(10, sizeof(char));
    printf("Ma fonction : \n");
    while(i < 10)
    {
        printf("%d", str[i]);
        i++;
    }
    printf("\n");
    printf("Fonction réelle : \n");
    i = 0;
    while(i < 10)
    {
        printf("%d", str2[i]);
        i++;
    }
    free(str);
    free(str2);
    return (0);
}*/
