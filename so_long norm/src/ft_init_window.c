
#include "../includes/so_long.h"

int	my_mlx_hook_callback(int keycode, t_game *game)
{
	exit(0);
}

void	ft_check_map(t_game *game)
{
	if (!ft_check_map_form(game->map.full))
	{
		ft_printf("Error\nMap is not rectangular! Exiting game.\n");
		exit (EXIT_FAILURE);
	}
	if (!ft_check_wall(game->map.full))
	{
		ft_printf("Error\nMap is not surrounded by wall.\n");
		exit (EXIT_FAILURE);
	}
	if (!ft_check_item(game))
	{
		ft_printf("Error\nInvalid elements, exiting game.\n");
		exit (EXIT_FAILURE);
	}
	if (!ft_verify_path(game->map.full))
	{
		ft_printf("Error\nCan't find valid path in this map, exiting game.\n");
		exit (EXIT_FAILURE);
	}
}

void	ft_init_window(t_game *game)
{
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * 16 + ((game->map.columns - 1) * 1), game->map.rows * 16 + ((game->map.rows - 1) * 1), "so_long");
	ft_init_floor(game);
	ft_init_images(game);
}
