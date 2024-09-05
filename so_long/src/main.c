#include "../includes/so_long.h"

int	main(int argc, char *argv[])
{
	t_game	*game;
	
	game->exit
	
	if (!ft_verify_arg(argc, argv))
		exit (EXIT_FAILURE);
	
	game = malloc(sizeof(t_game));
	//game->move_count = 0;
	game->mlx_ptr = mlx_init();
	ft_init_map(argv[1], &game->map);
	ft_check_map(game);
	game->total_collectables = ft_find_collectables(game);
	ft_init_window(game);
	game->move_count = 0;
	mlx_loop_hook(game->mlx_ptr, ft_loop_hook, game);
	mlx_key_hook(game->win_ptr, ft_key_hook, game);
	mlx_hook(game->win_ptr, 17, 0, my_mlx_hook_callback, game);
	mlx_loop(game->mlx_ptr);
}
/*
void	print_map(char ** tab) {
	char	**map_current;
	t_position	grid_pos;
	t_position	pixel_pos;
	int			delta_y;
	t_image		*img_current;
	
	grid_pos.y = 0;
	map_current = tab;
	printf("\n");
	while (map_current[grid_pos.y])
	{
		printf("%s\n", map_current[grid_pos.y]);
		grid_pos.y++;
	}
	printf("\n\n");
}*/
