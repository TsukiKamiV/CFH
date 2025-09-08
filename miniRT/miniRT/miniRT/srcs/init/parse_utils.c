/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:20:39 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 13:23:18 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	add_object(t_scene *scene, t_object *new)
{
	t_object	*current;

	if (!scene->objs)
	{
		scene->objs = new;
		return ;
	}
	current = scene->objs;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	validate_assign_rgb(t_color *color, char **rgb)
{
	int	i;
	int	v;

	i = 0;
	if (ft_count_size(rgb) != 3)
		return (error_msg("wrong color parameter count.", 1));
	while (i < 3)
	{
		v = ft_atoi(rgb[i]);
		if (v < 0 || v > 255)
			return (error_msg("color component out of range.", 1));
		i++;
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	return (0);
}

int	normal_is_unit(t_vec3 n)
{
	double	len;

	len = vec3_length(n);
	if (len < 0.99 || len > 1.01)
		return (1);
	return (0);
}

int	create_and_fill_obj(t_scene *scene, t_object_type type, void *element)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(element);
		return (error_msg("object allocation failed.", 1) && 0);
	}
	obj->type = type;
	obj->element = element;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}

void	free_lines(t_params *ls)
{
	int	i;

	if (!ls || !ls->tab)
		return ;
	i = 0;
	while (i < ls->count)
	{
		if (ls->tab[i])
			free (ls->tab[i]);
		i++;
	}
	free (ls->tab);
	ls->tab = NULL;
	ls->count = 0;
}
