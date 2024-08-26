#include "../includes/so_long.h"


int	ft_key_hook(int keycode, t_game *game)
{
	printf("keycode pressed: %d!\n", keycode);
	if (keycode == 53 || keycode == 12)
		close_window(keycode, game);
	if ((keycode == KEYCODE_ARROW_UP || keycode == KEYCODE_WASD_UP) && (game->map.full[game->person_pos.y - 1][game->person_pos.x] != '1'))
	{
		
		printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y - 1][game->person_pos.x] == 'C')
		{
			game->total_collectables--;
			printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y - 1][game->person_pos.x] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		printf("UP DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x, game->person_pos.y - 1);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->map.full[game->person_pos.y - 1][game->person_pos.x] = 'B';
	}
	if ((keycode == KEYCODE_ARROW_DOWN || keycode == KEYCODE_WASD_DOWN) && (game->map.full[game->person_pos.y + 1][game->person_pos.x] != '1'))
	{
		printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y + 1][game->person_pos.x] == 'C')
		{
			game->total_collectables--;
			printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y + 1][game->person_pos.x] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		printf("DOWN DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x, game->person_pos.y + 1);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->map.full[game->person_pos.y + 1][game->person_pos.x] = 'F';
	}
	if ((keycode == KEYCODE_ARROW_LEFT || keycode == KEYCODE_WASD_LEFT) && (game->map.full[game->person_pos.y][game->person_pos.x - 1] != '1'))
	{
		printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y][game->person_pos.x - 1] == 'C')
		{
			game->total_collectables--;
			printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y][game->person_pos.x - 1] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		printf("LEFT DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x - 1, game->person_pos.y);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->map.full[game->person_pos.y][game->person_pos.x - 1] = 'L';
	}
	if ((keycode == KEYCODE_ARROW_RIGHT || keycode == KEYCODE_WASD_RIGHT) && (game->map.full[game->person_pos.y][game->person_pos.x + 1] != '1'))
	{
		printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y][game->person_pos.x + 1] == 'C')
		{
			game->total_collectables--;
			printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y][game->person_pos.x + 1] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		printf("RIGHT DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x + 1, game->person_pos.y);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->map.full[game->person_pos.y][game->person_pos.x + 1] = 'R';
	}
	return (0);
}

int	ft_loop_hook(t_game *game)
{
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	ft_put_floor(*game);
	ft_render_map(game);
	return (0);
}
