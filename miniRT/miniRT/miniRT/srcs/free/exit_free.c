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

int my_mlx_hook_callback(int code, void *param)
{
	t_scene *scene;
	
	(void)code;
	scene = (t_scene *)param;
	close_program(scene, NULL, EXIT_SUCCESS_KEY);
	return (0);
}
