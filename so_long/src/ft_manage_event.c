#include "../includes/so_long.h"


int	ft_key_hook(int keycode, t_game *game)
{
	int dx, dy, ret;
	//printf("keycode pressed: %d!\n", keycode);
	if (keycode == 53 || keycode == 12)
		close_window(keycode, game);
	
	dx = 0;
	dy = 0;
	//refacto
	if (keycode == KEYCODE_ARROW_UP || keycode == KEYCODE_WASD_UP) {
		dy = -1;
	}
	if (keycode == KEYCODE_ARROW_DOWN || keycode == KEYCODE_WASD_DOWN) {
		dy = 1;
	}
	if (keycode == KEYCODE_ARROW_LEFT || keycode == KEYCODE_WASD_LEFT) {
		dx = -1;
	}
	if (keycode == KEYCODE_ARROW_RIGHT || keycode == KEYCODE_WASD_RIGHT) {
		dx = 1;
	}
	
	if (dx == 0 && dy == 0)
		return (0);
	
	ret = ft_handle_move_trend(dx, dy, game);
	return (ret);
	/*
	//before refacto
	if ((keycode == KEYCODE_ARROW_UP || keycode == KEYCODE_WASD_UP) && (game->map.full[game->person_pos.y - 1][game->person_pos.x] != '1'))
	{
		game->move_count++;
		ft_printf("%d\n", game->move_count);
		//以下为新增部分，用于整合优化：
		game->person_next.y = game->person_pos.y - 1;
		game->person_next.x = game ->person_pos.x;
		ft_catch_keycode(keycode, game);
		
		
		//printf("%d collectables left.\n", game->total_collectables);
		//这里可以抽象为game->person_next;
		ft_catch_keycode(keycode, game);
		if (game->map.full[game->person_pos.y - 1][game->person_pos.x] == 'C')
		{
			game->total_collectables--;
			//printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y - 1][game->person_pos.x] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		//printf("UP DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x, game->person_pos.y - 1);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->person_pos.y--;
		game->map.full[game->person_pos.y][game->person_pos.x] = 'B';
		
	}
	if ((keycode == KEYCODE_ARROW_DOWN || keycode == KEYCODE_WASD_DOWN) && (game->map.full[game->person_pos.y + 1][game->person_pos.x] != '1'))
	{
		game->move_count++;
		ft_printf("%d\n", game->move_count);
		//printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y + 1][game->person_pos.x] == 'C')
		{
			game->total_collectables--;
			//printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y + 1][game->person_pos.x] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		//printf("DOWN DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x, game->person_pos.y + 1);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->person_pos.y++;
		game->map.full[game->person_pos.y][game->person_pos.x] = 'F';
	}
	if ((keycode == KEYCODE_ARROW_LEFT || keycode == KEYCODE_WASD_LEFT) && (game->map.full[game->person_pos.y][game->person_pos.x - 1] != '1'))
	{
		game->move_count++;
		ft_printf("%d\n", game->move_count);
		//printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y][game->person_pos.x - 1] == 'C')
		{
			game->total_collectables--;
			//printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y][game->person_pos.x - 1] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		//printf("LEFT DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x - 1, game->person_pos.y);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->person_pos.x--;
		game->map.full[game->person_pos.y][game->person_pos.x] = 'L';
	}
	if ((keycode == KEYCODE_ARROW_RIGHT || keycode == KEYCODE_WASD_RIGHT) && (game->map.full[game->person_pos.y][game->person_pos.x + 1] != '1'))
	{
		game->move_count++;
		ft_printf("%d\n", game->move_count);
		//printf("%d collectables left.\n", game->total_collectables);
		if (game->map.full[game->person_pos.y][game->person_pos.x + 1] == 'C')
		{
			game->total_collectables--;
			//printf("%d collectables left.\n", game->total_collectables);
		}
		if (game->total_collectables == 0 && game->map.full[game->person_pos.y][game->person_pos.x + 1] == 'E')
		{
			ft_printf("YOU WIN!!\n");
			close_window(keycode, game);
		}
		//printf("RIGHT DETECTED, current-pos: (%d, %d) next:(%d, %d)\n", game->person_pos.x, game->person_pos.y, game->person_pos.x + 1, game->person_pos.y);
		if (game->person_pos.x == game->exit_pos.x && game->person_pos.y == game->exit_pos.y && game->total_collectables != 0)
			game->map.full[game->person_pos.y][game->person_pos.x] = 'E';
		else
			game->map.full[game->person_pos.y][game->person_pos.x] = '0';
		game->person_pos.x++;
		game->map.full[game->person_pos.y][game->person_pos.x] = 'R';
	}
	//print_map(game->map.full);
	return (0);
	 */
}

void ft_restore_previous(t_position position, t_game *game)
{
	if (position.x == game->exit_pos.x && position.y == game->exit_pos.y && game->total_collectables != 0)
		game->map.full[position.y][position.x] = 'E';
	else
		game->map.full[position.y][position.x] = '0';
}

void ft_update_orientation(int dx, int dy, t_position position, t_game *game)
{
	char orientation;
	
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
	//game->person_pos.y = position.y;
}

int	ft_handle_move_trend(int dx, int dy, t_game *game)
{
	t_position next_position;
	char next;
	
	next_position.x = game->person_pos.x + dx;
	next_position.y = game->person_pos.y + dy;
	
	next = (char)game->map.full[next_position.y][next_position.x];
	
	//1. Check: movable
	if (next == '1')
		return (0);
	
	game->move_count++;
	
	//2. Check win case
	if (next == 'E' && game->total_collectables == 0) {
		ft_printf("YOU WIN!\n");
		close_window(0, game);
	}
	
	//3. Restore previous PersonPos data
	ft_restore_previous(game->person_pos, game);
	
	//4. Check if collect
	if (next == 'C')
		game->total_collectables--;
	
	//5. Write next person_pos data
	ft_update_orientation(dx, dy, next_position, game);
	return (0);
}

/*int	ft_mouse_hook(int button, t_game *game)
{
	if (keycode == KEY_CODE_MOUSE_CLOSE)
		close_window(keycode, game);
}*/

int	ft_loop_hook(t_game *game)
{
	//print_map(game->map.full);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	ft_put_floor(*game);
	ft_render_map(game);
	return (0);
}
