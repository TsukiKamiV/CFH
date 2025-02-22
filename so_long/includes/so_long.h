#ifndef SO_LONG_H
# define	SO_LONG_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"

# define PERSON_DY	-5

typedef struct	s_position
{
	int	x;
	int	y;
}				t_position;

typedef struct	s_size
{
	int	width;
	int	height;
}				t_size;


typedef struct	s_map
{
	char	**full;
	int	rows;
	int	columns;
	int	carrots;
	int	exit;
	int	players;
}	t_map;


typedef struct s_map_validator
{
	int	p_count;
	int	c_count;
	int	e_count;
	int invalid_count;
}				t_map_validator;

typedef struct	s_image
{
	void	*xpm_ptr;
	t_size	size;
	t_position position;
}	t_image;

//s_data from mlx docs
typedef struct	s_data{
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_data;

enum{
	KEYCODE_ARROW_UP = 126,
	KEYCODE_ARROW_DOWN = 125,
	KEYCODE_ARROW_LEFT = 123,
	KEYCODE_ARROW_RIGHT = 124,
	KEYCODE_WASD_UP = 13,
	KEYCODE_WASD_DOWN = 0,
	KEYCODE_WASD_LEFT = 1,
	KEYCODE_WASD_RIGHT = 2
};

typedef struct	s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	t_image	wall;
	t_image	floor;
	t_image	carrot;
	t_image	exit;
	t_image	start;
	t_image person;
	t_position person_pos;
	t_position	exit_pos;
	t_image	person_front;
	t_image	person_back;
	t_image	person_left;
	t_image	person_right;
	int	total_collectables;
	int	move_count;
}	t_game;

int	main(int argc, char *argv[]);

t_map	ft_init_map(char *map);

int	ft_verify_arg(int argc, char *argv[]);

void	ft_init_window(t_game *game);

void	ft_check_map(t_game *game);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	ft_init_img(t_game game);

void	ft_init_floor(t_game *game);

void	ft_put_floor(t_game game);

void	ft_init_images(t_game *game);

t_image	*ft_facing(t_game *game, char c, int *delta_y);

t_image *ft_process_elements(t_game *game, t_position grid_pos, char c);

void	ft_render_map(t_game *game, char **map);

///include exit(0);
int		close_window(t_game *game);

int	ft_key_hook(int keycode, t_game *game);

int	ft_mouse_hook(int button, t_game *game);

int	ft_loop_hook(t_game *game);

void	ft_manage_event(t_game *game);

int	ft_find_collectables(t_game *game);

void  flood_fill(char **tab, t_position size, t_position begin);

int	ft_verify_path(char **tab);

void	find_p(char **tab_copy, t_position size, t_position *begin);

int	ft_check_wall(char **tab);

int	ft_check_item(t_game *game);

void	ft_check_item_annex(char **tab, t_position size, t_map_validator *map_validator);

int	ft_check_map_form(char **tab);

void	ft_free_map(t_game *game);

void	ft_destroy_images(t_game *game);

void	ft_free_all_allocated_memory(t_game *game);

void	ft_empty_line(char *map);

void	ft_catch_keycode(int keycode, t_game *game);

///return 1: ok, return 0: wall
int	ft_handle_move_trend(int dx, int dy, t_game *game);

//runtime debugging
void	print_map(char **tab);

int	my_mlx_hook_callback(int keycode, t_game *game);

int	ft_detect_c(char c);

void	ft_error_exit(t_game *game);

//# define WIN_WIDTH	game.map.columns * 16
//# define WIN_HEIGHT	game.map.rows * 16
# define CARROTS_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/carrot.xpm"
# define WALL_PATH	"/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/wall-2.xpm"
# define PERSON_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/person_front.xpm"
# define EXIT_PATH	"/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/exit.xpm"
# define START_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/start.xpm"
# define PERSON_FRONT_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/person_front.xpm"
# define PERSON_BACK_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/person_back.xpm"
# define PERSON_LEFT_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/person_left.xpm"
# define PERSON_RIGHT_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/person_right.xpm"
# define FLOOR_TILE_PATH "/Users/luyao/Projects/CFH/so_long_bak/assets/sprites/floor.xpm"

# define draw_img(mlx_ptr, win_ptr, img_ptr, x, y) mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, x, y)
#endif
