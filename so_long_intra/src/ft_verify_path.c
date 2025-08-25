/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:19:08 by luxu              #+#    #+#             */
/*   Updated: 2024/10/03 13:41:13 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**ft_make_tab_copy(char **tab, t_position *size)
{
	char	**tab_copy;
	int		row_index;
	int		row_counting;

	row_counting = 0;
	while (tab[row_counting] != NULL)
		row_counting++;
	tab_copy = malloc(sizeof(char *) * row_counting);
	if (!tab_copy)
		return (NULL);
	row_index = 0;
	while (row_index < row_counting)
	{
		tab_copy[row_index] = ft_strdup(tab[row_index]);
		row_index++;
	}
	size->x = (int)ft_strlen(tab[0]);
	size->y = row_counting;
	return (tab_copy);
}

void	ft_free_tab_copy(char **tab, int row_count)
{
	int	i;

	i = 0;
	while (i < row_count)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	find_p(char **tab_copy, t_position size, t_position *begin)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size.y)
	{
		j = 0;
		while (j < size.x)
		{
			if (tab_copy[i][j] == 'P')
			{
				begin->y = i;
				begin->x = j;
			}
			j++;
		}
		i++;
	}
}

int	ft_verify_path(char **tab)
{
	t_position	size;
	t_position	begin;
	t_position	index;
	char		**tab_copy;
	int			ret;

	tab_copy = ft_make_tab_copy(tab, &size);
	find_p(tab_copy, size, &begin);
	flood_fill(tab_copy, size, begin);
	index.y = 0;
	ret = 1;
	while (index.y < size.y)
	{
		index.x = 0;
		while (index.x < size.x)
		{
			if (tab_copy[index.y][index.x] == 'C' \
					|| tab_copy[index.y][index.x] == 'E')
				ret = 0;
			index.x++;
		}
		index.y++;
	}
	ft_free_tab_copy(tab_copy, size.y);
	return (ret);
}
