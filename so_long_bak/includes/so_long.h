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


typedef enum	e_bool
{
	false,
	true
}	t_bool;

typedef struct	s_position
{
	int	x;
	int	y;
}				t_position;

typedef struct	s_map
{
	char	**full;
	int	rows;
	int	columns;
	int	carrots;
	int	exit;
	int	players;
	t_position	player;
}	t_map;

typedef struct	s_image
{
	void	*xpm_ptr;
	int				x;
	int				y;
}	t_image;

typedef struct	s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	t_image	wall;
	t_image	floor;
	t_image	carrots;
	t_image	exit;
	t_image	start;
	t_image	player_front;
	t_image	player_back;
	t_image	left;
	t_image	right;
}	t_game;

int	main(int argc, char *argv[]);

int	ft_verify_map(int argc, char *argv[]);
#endif
