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

//int my_mlx_hook_callback(int code, void *param)
//{
//	t_scene *scene;
//
//	(void)code;
//	scene = (t_scene *)param;
//	close_program(scene, NULL, EXIT_SUCCESS_MLX);
//	return (0);
//}


int	my_mlx_hook_callback(void *param)
{
	t_scene  *scene;
	//t_scene **as_double;

	//(void)code;
	//printf("%d\n", code);
	scene  = (t_scene *)param;
	//as_double = (t_scene **)param;
	//printf("param addr: %p\n", param);
	//fprintf(stderr,
	//		"[hook] param=%p  as_scene=%p  *as_double=%p\n",
	//		param, (void*)as_scene,
	//		(as_double ? (void*)*as_double : NULL));
	/* 如果你在注册时误传了 &scene，那么这里的 *as_double
	 很可能正好就是你真正的 scene 指针；而 as_scene 则是垃圾地址。 */
	close_program(scene, NULL, EXIT_SUCCESS_MLX);
	return (0);
}
