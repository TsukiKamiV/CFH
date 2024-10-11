#include "../includes/so_long.h"

t_map	ft_init_map(char *map)
{
	int	fd;
	t_map	ret;
	char	*line_tmp;
	char	*map_tmp;
	
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCannot open map, stopping game.\n");
		exit (EXIT_FAILURE);
	}
	ret.rows = 0;
	map_tmp = ft_strdup("");
	while (1)
	{
		line_tmp = get_next_line(fd);
		if (line_tmp == NULL)
			break;
		//printf("%s", line_tmp);
		ret.columns = (int)ft_strlen(line_tmp) - 1;
		map_tmp = ft_strjoin(map_tmp, line_tmp);//join里面也有malloc
		free (line_tmp);
		ret.rows++;
	}
	close(fd);
	ft_empty_line(map_tmp);
	ret.full = ft_split(map_tmp, '\n');
	free (map_tmp);
	return (ret);
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
