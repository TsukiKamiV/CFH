/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:17:10 by luxu              #+#    #+#             */
/*   Updated: 2024/10/14 12:23:55 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_check_item_annex(char **tab, int width, int height, \
		t_map_validator *map_validator);

int	ft_check_map_form(char **tab, int *columns, int *rows)
{
	int	len;
	int	len0;
	int	i;
	int	lines;

	lines = 0;
	len0 = (int)ft_strlen(tab[0]);
	while (tab[lines])
		lines++;
	i = 1;
	while (i < lines)
	{
		len = (int)ft_strlen(tab[i]);
		if (len != len0)
			return (0);
		i++;
	}
	*columns = len0;
	*rows = lines;
	return (1);
}

int	ft_check_item(t_map map)
{
	char			**tab;
	t_map_validator	map_validator;

	tab = map.full;
	map_validator = (t_map_validator){0, 0, 0, 0};
	ft_check_item_annex(tab, map.columns, map.rows, &map_validator);
	return (map_validator.p_count == 1 && map_validator.invalid_count == 0 && \
			map_validator.e_count == 1 && map_validator.c_count >= 1);
}

void	ft_check_item_annex(char **tab, int width, int height, \
							t_map_validator *map_validator)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			c = tab[i][j];
			if (c != 'E' && c != 'P' && c != 'C' && c != '0' && c != '1')
				map_validator->invalid_count++;
			if (c == 'C')
				map_validator->c_count++;
			if (c == 'E')
				map_validator->e_count++;
			if (c == 'P')
				map_validator->p_count++;
			j++;
		}
		i++;
	}
}

void	ft_empty_line(char *map)
{
	int	i;

	if (map[0] == '\n')
	{
		ft_printf("Error\nEmpty line in map, exiting game.\n");
		free (map);
		exit (EXIT_FAILURE);
	}
	else if (*map == '\0')
	{
		ft_printf("Error\nEmpty Map, exiting game.\n");
		free (map);
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			ft_printf("Error\nEmpty line in map, exiting game.\n");
			free (map);
			exit (EXIT_FAILURE);
		}
		i++;
	}
}

int	ft_check_wall(char **tab, int columns, int rows)
{
	int			i;
	int			j;

	i = 0;
	while (i < rows)
	{
		if (tab[i][0] != '1' || tab[i][columns - 1] != '1')
			return (0);
		if (i == 0 || i == rows - 1)
		{
			j = 1;
			while (j < columns - 1)
			{
				if (tab[i][j] != '1')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}
