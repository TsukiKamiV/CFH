
#include "../includes/so_long.h"

void	ft_init_window(t_game *game, char *map)
{
	game->mlx_ptr = mlx_init();
	ft_init_map(map, &game->map);
	printf("There're %d carrots in this map.\n", ft_find_collectables(game));
	//printf("map has %d columns and %d rows\n", game->map.columns, game->map.rows);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * 16 + ((game->map.columns - 1) * 1), game->map.rows * 16 + ((game->map.rows - 1) * 1), "so_long");
	ft_init_floor(game);
	ft_init_images(game);
	//ft_put_floor(*game);
	//ft_render_map(game);
	mlx_loop_hook(game->mlx_ptr, ft_loop_hook, game);
	mlx_key_hook(game->win_ptr, ft_key_hook, game);
	mlx_loop(game->mlx_ptr);
}


/*void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}*/

/*
int width = 4;
int bits_per_pixel = 1234;
int distanceInMeter = bits_per_pixel / 8
int line_length = width * distanceInMeter
int hou_de_offset = ((y * width) + x) * distanceInMeter
int shazi_de_offset = y * line_length + x * (bits_per_pixel / 8)

int offset = (y * line_length + x * (bits_per_pixel / 8));*/

