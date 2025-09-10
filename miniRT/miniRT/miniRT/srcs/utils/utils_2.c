/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:08:20 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 16:10:17 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	free_multiple_tab(int count, ...)
{
	va_list	ap;
	char	**ptr;
	int		i;

	va_start(ap, count);
	i = 0;
	while (i < count)
	{
		ptr = va_arg(ap, char **);
		if (ptr)
			free_tab(ptr);
		i++;
	}
	va_end(ap);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
