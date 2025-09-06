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

void	destroy_scene_image(t_scene *scene)
{
	t_image	*img;
	
	if (!scene)
		return ;
	img = scene->img;
	if (!img)
		return ;
	if (scene->mlx_ptr && (img->img_ptr != NULL))
		mlx_destroy_image(scene->mlx_ptr, img->img_ptr);
	free (img);
	scene->img = NULL;
}


int	close_program(t_scene *scene, const char *msg, int state)
{
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	if (scene)
	{
		destroy_scene_image(scene);
		if (scene->mlx_ptr	 && scene->win_ptr)
		{
			mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
			scene->win_ptr = NULL;
		}
		if (scene->mlx_ptr)
		{
			destroy_display(scene->mlx_ptr);
			free (scene->mlx_ptr);
			scene->mlx_ptr = NULL;
		}
		free_scene(scene);
		free (scene);
	}
	exit(state);
}
