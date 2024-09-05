#include "../includes/so_long.h"

void	ft_init_map(char *map, t_map *map_struct)
{
	int	fd;
	char	*line_tmp;
	char	*map_tmp;
	
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCannot open map, stopping game.\n");
		exit (EXIT_FAILURE);
	}
	map_struct->rows = 0;
	map_tmp = ft_strdup("");
	while (1)
	{
		line_tmp = get_next_line(fd);
		if (line_tmp == NULL)
			break;
		printf("%s", line_tmp);
		map_struct->columns = ft_strlen(line_tmp) - 1;//这里不应该重复计算，但循环外无法获得line_tmp,需要优化
		map_tmp = ft_strjoin(map_tmp, line_tmp);
		free (line_tmp);
		map_struct->rows++;
	}
	close(fd);
	ft_empty_line(map_tmp);
	//printf("map has %d columns and %d rows", map_struct->columns, map_struct->rows);
	map_struct->full = ft_split(map_tmp, '\n');
	free (map_tmp);
}

int	ft_find_collectables(t_game *game) //这里还兼顾了初始化person_pos的功能，可能需要给函数改名 （但是为什么重新定义一个遍历地图寻找P的函数就报错退出？？）
{
	char	**map;
	int	line;
	int	i;
	
	line = 0;
	game->total_collectables = 0;
	map = game->map.full;
	while (map[line])
	{
		i = 0;
		while (map[line][i])
		{
			if (map[line][i] == 'C')
				game->total_collectables++;
			else if (map[line][i] == 'P')
			{
				game->person_pos.x = i;
				game->person_pos.y = line;
			}
			i++;
		}
		line++;
	}
	return (game->total_collectables);
}
/*
void	ft_find_person(t_game *game)
{
	char	**map;
	int	line;
	int	i;
	
	line = 0;
	map = game->map.full;
	while (map[line])
	{
		i = 0;
		while (map[line][i])
		{
			if (map[line][i] == 'P')
			{
				game->person_pos.x = i;
				game->person_pos.y = line;
			}
			i++;
		}
		line++;
	}
}*/
