#include "../includes/so_long.h"

/*void	ft_error_exit(t_game game, char *map)
{
	
}*/

int	close_window(t_game *game)
{
	//mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	ft_free_all_allocated_memory(game);
	exit(0);
}

void	ft_free_map(t_game *game)
{
	int	line;
	
	line = 0;
	while (line < game->map.rows)
		free(game->map.full[line++]);
	free(game->map.full);
}

void	ft_free_all_allocated_memory(t_game *game)
{
	ft_destroy_images(game);
	ft_free_map(game);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game->mlx_ptr);
	//free(game);
}

void	ft_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->carrot.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_front.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_back.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit.xpm_ptr);
}
