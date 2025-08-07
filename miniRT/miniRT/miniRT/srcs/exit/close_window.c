#include "../../includes/miniRT.h"

void	free_all_allocated_memory(t_scene *scene)
{
	free_scene(scene);
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	free(scene->mlx_ptr);
	free(scene);
}

int	close_window(t_scene *scene)
{
	free_all_allocated_memory(scene);
	exit(0);
	return (0);
}

