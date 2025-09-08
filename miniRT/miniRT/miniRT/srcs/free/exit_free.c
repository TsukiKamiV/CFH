/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:16:43 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 13:19:12 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	exit_with_lines(t_scene *scene, t_params *ls, const char *msg, int code)
{
	free_lines(ls);
	close_program(scene, msg, code);
}

int	my_mlx_hook_callback(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	close_program(scene, NULL, EXIT_SUCCESS_MLX);
	return (0);
}
