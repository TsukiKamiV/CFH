#include "../includes/so_long.h"

int	ft_verify_arg(int argc, char *argv[])
{
	size_t	argv_len;

	if (argc > 2)
	{
		ft_printf("Error\nToo many arguments\n");
		return (0);
	}
	if (argc < 2)
	{
		ft_printf("Error\nPlease load a map\n");
		return (0);
	}
	argv_len = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][argv_len - 4], ".ber", 4))
	{
		ft_printf("Error\nThe map should be a .ber file\n");
		return (0);
	}
	return (1);
}

int	ft_check_map_form(char **tab)
{
	int	len;
	int	len0;
	int	i;
	int	lines;
	
	lines = 0;
	len0 = ft_strlen(tab[0]);
	while (tab[lines])
		lines++;
	i = 1;
	while (i < lines)
	{
		len = ft_strlen(tab[i]);
		if (len != len0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_item(t_game *game)
{
	int	i;
	int	j;
	t_item_count count;
	t_position	size;
	char **tab;
	
	tab = game->map.full;
	size.y = ft_strlen(tab[0]);
	size.x = 0;
	count.c_count = 0;
	count.p_count = 0;
	count.e_count = 0;
	while (tab[size.x])
		size.x++;
	i = 0;
	while (i < size.x - 1)
	{
		j = 0;
		while (j < size.y - 1)
		{
			//[1]
			ft_check_item_annex(tab[i][j], game, &count, &size, i, j);
			if (tab[i][j] != 'E' &&tab[i][j] != 'P' && tab[i][j] != 'C' && tab[i][j] != '0' && tab[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	//if (count.p_count != 1 || count.e_count != 1 || count.c_count < 1)
	//	return (0);
	return (count.p_count == 1 || count.e_count == 1 || count.c_count >= 1);
	//return (1);
}

//[1]
//if (tab[i][j] == 'C')
//	count.c_count++;
//else if (tab[i][j] == 'E')
//	count.e_count++;
//else if (tab[i][j] == 'P')
//{
//	count.p_count++;
//	game->person_pos.x = j;
//	game->person_pos.y = i;
//}

void	ft_check_item_annex(char c, t_game *game, t_item_count *count, t_position *size, int i, int j)
{
	if (c == 'C')
		count->c_count++;
	else if (c == 'E')
		count->e_count++;
	else if (c == 'P')
	{
		count->p_count++;
		game->person_pos.x = j;
		game->person_pos.y = i;
	}
}

void	ft_empty_line(char *map)
{
	int	i;
	
	if (map[0] == '\n')
	{
		ft_printf("Error\nEmpty line in map, exiting game.\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			ft_printf("Error\nEmpty line in map, exiting game.\n");
			exit (EXIT_FAILURE);
		}
		i++;
	}
}

int	ft_check_wall(char **tab)
{
	int	i;
	int	j;
	t_position	size;
	
	size.y = ft_strlen(tab[0]);
	size.x = 0;
	while (tab[size.x])
		size.x++;
	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			if (i == 0 || i == size.x - 1)
			{
				if (tab[i][j] != '1')
					return (0);
			}
			else if (i != 0 && i != size.x - 1)
			{
				if (tab[i][0] != '1' || tab[i][size.y - 1] != '1')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
