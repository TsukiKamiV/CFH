#include "../../includes/miniRT.h"

#if defined(__linux__)

void	destroy_display(void *mlx_ptr)
{
	mlx_destroy_display(mlx_ptr);
}

#else

void	destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
}
#endif

//void	free_all_allocated_memory(t_scene *scene)
//{
//	free_scene(scene);
//	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
//	free(scene->mlx_ptr);
//	free(scene);
//}

//int	close_window(t_scene *scene)
//{
//	free_all_allocated_memory(scene);
//	exit(0);
//	return (0);
//}

//int	close_program(t_scene *scene, const char *msg, int state)
//{
//	if (state == 1)
//	{
//		if (scene->mlx_ptr)
//			destroy_display(scene->mlx_ptr);
//		free(scene->mlx_ptr);
//		return (error_msg("mlx initiation failed", 1));
//	}
//	return (0);
//}

//int	close_program(t_scene *scene, const char *msg, int //state)
//{
//	if (msg)
//		ft_putstr_fd((char *)msg, 2);
//	if (scene)
//	{
//		if (scene->mlx_ptr && scene->win_ptr)
//			mlx_destroy_window(scene->mlx_ptr, //scene->win_ptr);
//		if (scene->mlx_ptr)
//			destroy_display(scene->mlx_ptr);
//		free (scene->mlx_ptr);
//		free (scene);
//	}
//	exit(state);
//	return (0);
//}

int	close_program(t_scene *scene, const char *msg, int state)
{
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	if (scene)
	{
		if (scene->mlx_ptr && scene->win_ptr)
			mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
		if (scene->mlx_ptr)
			destroy_display(scene->mlx_ptr);
		free_scene(scene);
		free(scene->mlx_ptr);
		free(scene);
	}
	exit(state);
	return (0);
}
