/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:14:34 by luxu              #+#    #+#             */
/*   Updated: 2024/10/04 21:31:51 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	my_mlx_hook_callback(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	exit(0);
}

void	ft_check_map(t_map *map)
{
	if (!ft_check_map_form(map->full, &map->columns, &map->rows))
	{
		ft_printf("Error\nMap is not rectangular! Exiting game.\n");
		ft_free_map(map);
		exit (EXIT_FAILURE);
	}
	if (!ft_check_wall(map->full, map->columns, map->rows))
	{
		ft_printf("Error\nMap is not surrounded by wall.\n");
		ft_free_map(map);
		exit (EXIT_FAILURE);
	}
	if (ft_check_item(*map) != 1)
	{
		ft_printf("Error\nInvalid elements, exiting game.\n");
		ft_free_map(map);
		exit (EXIT_FAILURE);
	}
	if (!ft_verify_path(map->full))
	{
		ft_printf("Error\nCan't find valid path in this map, exiting game.\n");
		ft_free_map(map);
		exit (EXIT_FAILURE);
	}
}

void	ft_init_window(t_game *game)
{
	ft_init_floor(game);
	ft_init_images(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->map.columns * 16 + \
			((game->map.columns - 1) * 1), game->map.rows * 16 + \
			((game->map.rows - 1) * 1), "so_long");
	if (!game->win_ptr)
		ft_close_game(game, 2);
}
