/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:09:09 by luxu              #+#    #+#             */
/*   Updated: 2024/10/05 14:13:52 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (!ft_verify_arg(argc, argv))
		exit (EXIT_FAILURE);
	game.map = ft_init_map(argv[1]);
	ft_check_map(&game.map);
	game.total_collectables = count_c(game.map.full, &game.person_pos);
	game.move_count = 0;
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (ft_close_game(&game, 1), 1);
	ft_init_window(&game);
	mlx_loop_hook(game.mlx_ptr, ft_loop_hook, &game);
	mlx_key_hook(game.win_ptr, ft_key_hook, &game);
	mlx_hook(game.win_ptr, 17, 0, my_mlx_hook_callback, &game);
	mlx_loop(game.mlx_ptr);
}

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

void	draw_img(void *mlx_ptr, void *win_ptr, void *img_ptr, t_position pos)
{
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, pos.x, pos.y);
}
