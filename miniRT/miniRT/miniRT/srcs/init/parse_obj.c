#include "../../includes/miniRT.h"

int	parse_plane(char **tokens, t_scene *scene)
{
	t_object	*obj;
	t_plane		*pl;
	char		**pos;
	char		**normal;
	char		**color;
	
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error.\nInvalid plane format.", 2);
		return (0);
	}
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		ft_putstr_fd("Error.\nMalloc failed when creating plane.", 2);
		return (0);
	}
	pos = ft_split(tokens[1], ',');
	normal = ft_split(tokens[2], ',');
	color = ft_split(tokens[3], ',');
	
	if (!pos || !normal || !color)
	{
		ft_putstr_fd("Error.\nInvalid plane vector formatting.\n", 2);
		if (pos)
			free_tab(pos);
		if (normal)
			free_tab(normal);
		if (color)
			free_tab(color);
		free(pl);
		return (0);
	}
	
	pl->point.x = atof(pos[0]);
	pl->point.y = atof(pos[1]);
	pl->point.z = atof(pos[2]);
	
	pl->normal.x = atof(normal[0]);
	pl->normal.y = atof(normal[1]);
	pl->normal.z = atof(normal[2]);
	
	pl->color.r = ft_atoi(color[0]);
	pl->color.g = ft_atoi(color[1]);
	pl->color.b = ft_atoi(color[2]);
	
	free_tab(pos);
	free_tab(normal);
	free_tab(color);
	
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_putstr_fd("Error.\nMalloc failed for t_object.\n", 2);
		free(pl);
		return (0);
	}
	obj->type = PLANE;
	obj->element = pl;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}

int	parse_sphere(char **tokens, t_scene *scene)
{
	t_object	*obj;
	t_sphere	*sp;
	char		**center;
	char		**color;
	
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		ft_putstr_fd("Error.\nInvalid sphere format\n", 2);
		return (0);
	}
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		ft_putstr_fd("Error.\nFailed malloc for sphere.\n", 2);
		return (0);
	}
	center = ft_split(tokens[1], ',');
	color = ft_split(tokens[3], ',');
	if (!center || !color)
	{
		ft_putstr_fd("Error.\nInvalid sphere formatting.\n", 2);
		if (center)
			free_tab(center);
		if (color)
			free_tab(color);
		free (sp);
		return (0);
	}
	sp->center.x = atof(center[0]);
	sp->center.y = atof(center[1]);
	sp->center.z = atof(center[2]);
	sp->radius = atof(tokens[2]) / 2.0;
	sp->color.r = ft_atoi(color[0]);
	sp->color.g = ft_atoi(color[1]);
	sp->color.b = ft_atoi(color[2]);
	
	free_tab(center);
	free_tab(color);
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_putstr_fd("Error.\nFailed to malloc t_object.\n", 2);
		free (sp);
		return (0);
	}
	obj->type = SPHERE;
	obj->element = sp;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}

int	parse_cylinder(char **tokens, t_scene *scene)
{
	t_object	*obj;
	t_cylinder	*cy;
	char		**center;
	char		**axis;
	char		**color;
	double		radius;
	double		height;
	
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
	{
		ft_putstr_fd("Error.\nInvalid cylinder format\n", 2);
		return (0);
	}
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
	{
		ft_putstr_fd("Error.\nFailed malloc for cylinder.\n", 2);
		return (0);
	}
	radius = atof(tokens[3]) / 2.0;
	height = atof(tokens[4]);
	cy->radius = radius;
	cy->height = height;
	center = ft_split(tokens[1], ',');
	axis = ft_split(tokens[2], ',');
	color = ft_split(tokens[5], ',');
	if (!center || !axis || !color )//写个判断归一化向量范围的判断函数判断axis
	{
		ft_putstr_fd("Error.\nInvalid cylinder formatting.\n", 2);
		if (center)
			free_tab(center);
		if (axis)
			free_tab(axis);
		if (color)
			free_tab(color);
		free (cy);
		return (0);
	}
	cy->centre.x = atof(center[0]);
	cy->centre.y = atof(center[1]);
	cy->centre.z = atof(center[2]);
	
	cy->axis.x = atof(axis[0]);
	cy->axis.y = atof(axis[1]);
	cy->axis.z = atof(axis[2]);
	
	cy->color.r = ft_atoi(color[0]);
	cy->color.g = ft_atoi(color[1]);
	cy->color.b = ft_atoi(color[2]);
	
	free_tab(center);
	free_tab(axis);
	free_tab(color);
	
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_putstr_fd("Error.\nFailed to malloc t_object.\n", 2);
		free (cy);
		return (0);
	}
	obj->type = CYLINDER;
	obj->element = cy;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}
