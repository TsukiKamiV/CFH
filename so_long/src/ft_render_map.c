#include "../includes/so_long.h"

void	ft_init_images(t_game *game)
{
	game->person.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, PERSON_PATH, &game->person.size.width, &game->person.size.height);
	game->person_front.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, PERSON_FRONT_PATH, &game->person_front.size.width, &game->person_front.size.height);
	game->person_back.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, PERSON_BACK_PATH, &game->person_back.size.width, &game->person_back.size.height);
	game->person_left.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, PERSON_LEFT_PATH, &game->person_left.size.width, &game->person_left.size.height);
	game->person_right.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, PERSON_RIGHT_PATH, &game->person_right.size.width, &game->person_right.size.height);
	game->carrot.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, CARROTS_PATH, &game->carrot.size.width, &game->carrot.size.height);
	game->wall.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, WALL_PATH, &game->wall.size.width, &game->wall.size.height);
	game->exit.xpm_ptr = mlx_xpm_file_to_image(game->mlx_ptr, EXIT_PATH, &game->exit.size.width, &game->exit.size.height);
	if (!game->person.xpm_ptr || !game->carrot.xpm_ptr || !game->wall.xpm_ptr || !game->exit.xpm_ptr)
	{
		ft_printf("Error\nFaild to load the images, stopping game\n");
		exit (EXIT_FAILURE);
	}
}

void	ft_render_pos(t_game *game, char c, t_position grid)
{
	int			dy;
	t_image		*img;
	t_position pixel;
	
	dy = 0;
	if (ft_detect_c(c) == 0)
		img = ft_process_elements(game, grid, c);
	else
		img = ft_facing(game, c, &dy);
	pixel.y = (grid.y * (16 + 1)) + ((16 - img->size.height) / 2) + dy;
	pixel.x = (grid.x * (16 + 1)) + ((16 - img->size.width) / 2);
	draw_img(game->mlx_ptr, game->win_ptr, img->xpm_ptr, pixel.x, pixel.y);
}

void	ft_render_map(t_game *game, char **map)
{
	t_position	grid;
	char	c;
	
	grid.y = 0;
	while (map[grid.y])
	{
		grid.x = 0;
		while (map[grid.y][grid.x])
		{
			c = (char)map[grid.y][grid.x];
			if (c != '0')
				ft_render_pos(game, c, grid);
			grid.x++;
		}
		grid.y++;
	}
}

int	ft_detect_c(char c)
{
	if (c == 'C' || c == 'E' || c == '1')
		return (0);
	return (1);
}

t_image *ft_process_elements(t_game *game, t_position grid_pos, char c)
{
	t_image	*ret_image;
	
	ret_image = NULL;
	if (c == 'C')
		ret_image = &game->carrot;
	else if (c == '1')
		ret_image = &game->wall;
	else if (c == 'E')
	{
		game->exit_pos.x = grid_pos.x;
		game->exit_pos.y = grid_pos.y;
		ret_image = &game->exit;
	}
	return (ret_image);
}

t_image	*ft_facing(t_game *game, char c, int *delta_y)
{
	t_image *image;
	if (c == 'P')
		image = &game->person;
	else if (c == 'B')
		image = &game->person_back;
	else if (c == 'F')
		image = &game->person_front;
	else if (c == 'L')
		image = &game->person_left;
	else if (c == 'R')
		image = &game->person_right;
	*delta_y = PERSON_DY;
	return (image);
}

//[1]
//if ((char)map_current[grid_pos.y][grid_pos.x] == 'C')
//	img_current = &game->carrot;
//else if ((char)map_current[grid_pos.y][grid_pos.x] == '1')
//	img_current = &game->wall;
//else if ((char)map_current[grid_pos.y][grid_pos.x] == 'E')
//{
//	game->exit_pos.x = grid_pos.x;
//	game->exit_pos.y = grid_pos.y;
//	img_current = &game->exit;
//}




/*
 else if ((char)map_current[grid_pos.y][grid_pos.x] == 'P')
 {
 img_current = &game->person;
 delta_y = PERSON_DY;
 }
 else if ((char)map_current[grid_pos.y][grid_pos.x] == 'B')
 {
 img_current = &game->person_back;
 delta_y = PERSON_DY;
 }
 else if ((char)map_current[grid_pos.y][grid_pos.x] == 'F')
 {
 img_current = &game->person_front;
 delta_y = PERSON_DY;
 }
 else if ((char)map_current[grid_pos.y][grid_pos.x] == 'L')
 {
 img_current = &game->person_left;
 delta_y = PERSON_DY;
 }
 else if ((char)map_current[grid_pos.y][grid_pos.x] == 'R')
 {
 img_current = &game->person_right;
 delta_y = PERSON_DY;
 }*/
/*else
 {
 grid_pos.x++;//如果check item已经排除了地图中有其他元素的情况，这里就不需要else了
 continue;
 }*/
