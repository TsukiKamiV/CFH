/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:30:51 by luxu              #+#    #+#             */
/*   Updated: 2024/10/05 14:21:20 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_render_pos(t_game *game, char c, t_position grid)
{
	int			dy;
	t_image		*img;
	t_position	pixel;

	dy = 0;
	if (ft_detect_c(c) == 0)
		img = ft_process_elements(game, grid, c);
	else
		img = ft_facing(game, c, &dy);
	pixel.y = (grid.y * (16 + 1)) + ((16 - img->size.height) / 2) + dy;
	pixel.x = (grid.x * (16 + 1)) + ((16 - img->size.width) / 2);
	draw_img(game->mlx_ptr, game->win_ptr, img->xpm_ptr, pixel);
}

void	ft_render_map(t_game *game, char **map)
{
	t_position	grid;
	char		c;

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

t_image	*ft_process_elements(t_game *game, t_position grid_pos, char c)
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
	t_image	*image;

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
