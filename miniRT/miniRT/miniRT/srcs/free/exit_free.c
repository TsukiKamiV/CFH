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
	if (scene->objs)
		free_objects(scene->objs);
}

int	my_mlx_hook_callback(int keycode, t_scene *scene)
{
	if (keycode == 17)
	{
		free_all_allocated_memory(scene);
		free(scene);
	}
	exit(0);
}
