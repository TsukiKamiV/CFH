#include "../includes/so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;
	
	if (!ft_verify_arg(argc, argv))
		exit (EXIT_FAILURE);
	ft_init_window(&game, argv[1]);
}
