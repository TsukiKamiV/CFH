/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:10:35 by luxu              #+#    #+#             */
/*   Updated: 2024/10/04 21:29:31 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_map	ft_init_map(char *map_path)
{
	int		fd;
	t_map	ret;
	char	*line_tmp;
	char	*map_tmp;

	fd = open(map_path, O_RDONLY);
	ft_map_error_exit(fd);
	ret.rows = 0;
	map_tmp = ft_strdup("");
	while (1)
	{
		line_tmp = get_next_line(fd);
		if (line_tmp == NULL)
			break ;
		ret.columns = ft_strlen(line_tmp) - 1;
		ft_strexpand(&map_tmp, line_tmp);
		free (line_tmp);
		ret.rows++;
	}
	close(fd);
	ft_empty_line(map_tmp);
	ret.full = ft_split(map_tmp, '\n');
	free (map_tmp);
	return (ret);
}

int	count_c(char **tab, t_position *person_pos)
{
	int		line;
	int		i;
	int		ret;

	ret = 0;
	line = 0;
	while (tab[line])
	{
		i = 0;
		while (tab[line][i])
		{
			if (tab[line][i] == 'C')
				ret++;
			else if (tab[line][i] == 'P')
				*person_pos = (t_position){i, line};
			i++;
		}
		line++;
	}
	return (ret);
}

void	ft_map_error_exit(int fd)
{
	if (fd == -1)
	{
		ft_printf("Error Loading Map\n");
		exit (EXIT_FAILURE);
	}
}
