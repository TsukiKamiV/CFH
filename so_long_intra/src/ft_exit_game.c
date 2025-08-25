/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:42:56 by luxu              #+#    #+#             */
/*   Updated: 2024/10/05 14:07:04 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_close_game(t_game *game, int state)
{
	if (state == 1)
	{
		ft_free_map(&game->map);
		if (game->mlx_ptr)
			destroy_display(game->mlx_ptr);
		free (game->mlx_ptr);
	}
	if (state == 2)
	{
		ft_free_map(&game->map);
		ft_destroy_images(game);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		if (game->mlx_ptr)
			destroy_display(game->mlx_ptr);
		free (game->mlx_ptr);
	}
	exit (0);
	return (0);
}

int	close_window(t_game *game)
{
	ft_free_all_allocated_memory(game);
	exit (0);
}

void	ft_free_map(t_map *map)
{
	int	line;

	line = 0;
	while (line < map->rows)
		free(map->full[line++]);
	free (map->full);
}

void	ft_free_all_allocated_memory(t_game *game)
{
	ft_destroy_images(game);
	ft_free_map(&game->map);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free (game->mlx_ptr);
}

void	ft_destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->wall.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->carrot.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_front.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_left.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_right.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->person_back.xpm_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit.xpm_ptr);
}
