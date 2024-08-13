//
//  main.c
//  so_long
//
//  Created by Luyao Xu on 13/08/2024.
//

#include <stdio.h>
//#include "../mlx/mlx.h"
#include "../includes/so_long.h"

int	main(int argc, char *argv[])
{
	void	*mlx;
	void	*mlx_win;
	
	if (!ft_verify_map(argc, argv))
		return (0);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "so_long");
	mlx_loop(mlx);
}
