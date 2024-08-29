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

void	ft_render_map(t_game *game)
{
	char	**map_current;
	t_position	grid_pos;
	t_position	pixel_pos;
	int			delta_y;
	t_image		*img_current;
	
	grid_pos.y = 0;
	map_current = game->map.full;
	while (map_current[grid_pos.y])
	{
		grid_pos.x = 0;
		while (map_current[grid_pos.y][grid_pos.x])
		{
			delta_y = 0;
			if ((char)map_current[grid_pos.y][grid_pos.x] == 'C')
				img_current = &game->carrot;
			else if ((char)map_current[grid_pos.y][grid_pos.x] == '1')
				img_current = &game->wall;
			else if ((char)map_current[grid_pos.y][grid_pos.x] == 'E')
			{
				game->exit_pos.x = grid_pos.x;
				game->exit_pos.y = grid_pos.y;
				img_current = &game->exit;
			}
			else if ((char)map_current[grid_pos.y][grid_pos.x] == 'P')
			{
				game->person_pos.x = grid_pos.x;
				game->person_pos.y = grid_pos.y;
				img_current = &game->person;
				delta_y = PERSON_DY;
			}
			else if ((char)map_current[grid_pos.y][grid_pos.x] == 'B')
			{
				game->person_pos.x = grid_pos.x;
				game->person_pos.y = grid_pos.y;
				img_current = &game->person_back;
				delta_y = PERSON_DY;
			}
			else if ((char)map_current[grid_pos.y][grid_pos.x] == 'F')
			{
				game->person_pos.x = grid_pos.x;
				game->person_pos.y = grid_pos.y;
				img_current = &game->person_front;
				delta_y = PERSON_DY;
			}
			else if ((char)map_current[grid_pos.y][grid_pos.x] == 'L')
			{
				game->person_pos.x = grid_pos.x;
				game->person_pos.y = grid_pos.y;
				img_current = &game->person_left;
				delta_y = PERSON_DY;
			}
			else if ((char)map_current[grid_pos.y][grid_pos.x] == 'R')
			{
				game->person_pos.x = grid_pos.x;
				game->person_pos.y = grid_pos.y;
				img_current = &game->person_right;
				delta_y = PERSON_DY;
			}
			else
			{
				grid_pos.x++;
				continue;
			}
			pixel_pos.y = (grid_pos.y * (16 + 1)) + ((16 - img_current->size.height) / 2) + delta_y;
			pixel_pos.x = (grid_pos.x * (16 + 1)) + ((16 - img_current->size.width) / 2);
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img_current->xpm_ptr, pixel_pos.x, pixel_pos.y);
			grid_pos.x++;
		}
		grid_pos.y++;
	}
}
