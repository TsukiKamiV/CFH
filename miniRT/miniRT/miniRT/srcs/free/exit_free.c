#include "../../includes/miniRT.h"

void	free_objects(t_object *obj)
{
	t_object	*tmp;
	
	while (obj)
	{
		tmp = obj->next;
		if (obj->type == SPHERE || obj->type == PLANE || obj->type == CYLINDER)
			free(obj->element);
		free(obj);
		obj = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->amb)
		free(scene->amb);
	if (scene->cam)
		free(scene->cam);
	if (scene->light)
		free(scene->light);
	if (scene->img)
	{
		mlx_destroy_image(scene->mlx_ptr, scene->img->img_ptr);
		free (scene->img);
	}
	if (scene->objs)
		free_objects(scene->objs);
}

int	my_mlx_hook_callback(int keycode, t_scene *scene)
{
	if (keycode == 17)
	{
		//free_all_allocated_memory(scene);
		close_program(scene, NULL, EXIT_SUCCESS_KEY);
		free(scene);
	}
	exit(0);
}

//void	exit_with_cleanup(t_scene *scene, char ***tabs, const char *msg, int code)
//{
//	int	i;
//
//	i = 0;
//	if (tabs)
//	{
//		while (tabs[i])
//		{
//			free_tab(tabs[i]);
//			i++;
//		}
//	}
//	close_program(scene, msg, code);
//}
