/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpantign <maildelulua42@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:15:07 by lpantign          #+#    #+#             */
/*   Updated: 2024/06/03 22:40:28 by lpantign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	char			*tmp;

	uc = (unsigned char)c;
	tmp = NULL;
	while (*s)
	{
		if (*s == uc)
			tmp = (char *)s;
		s++;
		if (!(*s) && uc != '\0')
			return (tmp);
	}
	if (uc == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char *str = ft_strrchr("laloooalu", 'a');
	printf("%s", str);
	return (0);
}
*/
