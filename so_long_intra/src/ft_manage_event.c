/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:16:30 by luxu              #+#    #+#             */
/*   Updated: 2024/10/04 21:32:21 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_key_hook(int keycode, t_game *game)
{
	int	dx;
	int	dy;
	int	ret;

	if (keycode == 65307 || keycode == 113)
		ft_close_game(game, 2);
	dx = 0;
	dy = 0;
	if (keycode == KEYCODE_ARROW_UP || keycode == KEYCODE_WASD_UP)
		dy = -1;
	if (keycode == KEYCODE_ARROW_DOWN || keycode == KEYCODE_WASD_DOWN)
		dy = 1;
	if (keycode == KEYCODE_ARROW_LEFT || keycode == KEYCODE_WASD_LEFT)
		dx = -1;
	if (keycode == KEYCODE_ARROW_RIGHT || keycode == KEYCODE_WASD_RIGHT)
		dx = 1;
	if (dx == 0 && dy == 0)
		return (0);
	ret = ft_handle_move_trend(dx, dy, game);
	return (ret);
}

void	ft_restore_previous(t_position position, t_game *game)
{
	if (position.x == game->exit_pos.x && \
			position.y == game->exit_pos.y && game->total_collectables != 0)
		game->map.full[position.y][position.x] = 'E';
	else
		game->map.full[position.y][position.x] = '0';
}

void	ft_update_orientation(int dx, int dy, t_position position, t_game *game)
{
	char	orientation;

	if (dx == -1)
		orientation = 'L';
	if (dx == 1)
		orientation = 'R';
	if (dy == -1)
		orientation = 'B';
	if (dy == 1)
		orientation = 'F';
	game->map.full[position.y][position.x] = orientation;
	game->person_pos = position;
}

int	ft_handle_move_trend(int dx, int dy, t_game *game)
{
	t_position	next_position;
	char		next;

	next_position.x = game->person_pos.x + dx;
	next_position.y = game->person_pos.y + dy;
	next = (char)game->map.full[next_position.y][next_position.x];
	if (next == '1')
		return (0);
	game->move_count++;
	ft_printf("%d\n", game->move_count);
	if (next == 'E' && game->total_collectables == 0)
	{
		ft_printf("YOU WIN!\n");
		ft_close_game(game, 2);
	}
	ft_restore_previous(game->person_pos, game);
	if (next == 'C')
		game->total_collectables--;
	ft_update_orientation(dx, dy, next_position, game);
	return (0);
}

int	ft_loop_hook(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	ft_put_floor(*game);
	ft_render_map(game, game->map.full);
	return (0);
}
