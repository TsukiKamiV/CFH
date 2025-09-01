#include "../../includes/miniRT.h"

static int	split_plane_tokens(char **tokens, char ***pos, char ***normal, char ***color)
{
	*pos = NULL;
	*normal = NULL;
	*color = NULL;
	*pos = ft_split(tokens[1], ',');
	*normal = ft_split(tokens[2], ',');
	*color = ft_split(tokens[3], ',');
	if (!(*pos) || !(*normal) || !(*color))
	{
		free_multiple_tab(4, *pos, *normal, *color, tokens);
		return (error_msg("invalid plane vector formatting.", 1));
	}
	if (ft_count_size(*pos) != 3 || ft_count_size(*normal) != 3 || ft_count_size(*color) != 3)
	{
		free_multiple_tab(4, *pos, *normal, *color, tokens);
		return (error_msg("invalid plane parameter size.", 1));
	}
	return (0);
}

static void	assign_plane_point_normal(t_plane *pl, char **pos, char **normal)
{
	pl->point.x = atof(pos[0]);
	pl->point.y = atof(pos[1]);
	pl->point.z = atof(pos[2]);
	pl->normal.x = atof(normal[0]);
	pl->normal.y = atof(normal[1]);
	pl->normal.z = atof(normal[2]);
}

static int	fill_plane(t_scene *scene, char **tokens, t_plane *pl, t_params *ls)
{
	char	**pos;
	char	**normal;
	char	**color;
	
	pos = NULL;
	normal = NULL;
	color = NULL;
	if (split_plane_tokens(tokens, &pos, &normal, &color))
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
		//return (1);
	assign_plane_point_normal(pl, pos, normal);
	if (normal_is_unit(pl->normal))
	{
		free_multiple_tab(4, pos, normal, color, tokens);
		free (pl);
		exit_with_lines(scene, ls, "Error: plane normal must be normalized.\n", EXIT_ERROR_PARAM);
		//close_program(scene, "Error: plane normal must be normalized.\n", EXIT_ERROR_PARAM);
		//return (error_msg("plane normal must be normalized.", 1));
	}
	if (validate_assign_rgb(&pl->color, color))
	{
		free_multiple_tab(4, pos, normal, color, tokens);
		free (pl);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
		//close_program(scene, NULL, EXIT_ERROR_PARAM);
		//return (1);
	}
	free_multiple_tab(3, pos, normal, color);
	return (0);
}

int	parse_plane(char **tokens, t_scene *scene, t_params *ls)
{
	t_plane		*pl;
	t_object	*obj;
	
	//(void)ls;
	if (ft_count_size(tokens) != 4)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: invalid plane parameter number.\n", EXIT_ERROR_PARAM);
	}
		//close_program(scene, "Error: invalid plane parameter number.\n", EXIT_ERROR_PARAM);
		//return (error_msg("invalid plane parameter count.", 1));
	pl = malloc(sizeof(t_plane));
	if (!pl)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: allocation failed for t_plane.\n", EXIT_ERROR_MALLOC);
	}
		//close_program(scene, "Error: allocation failed for t_plane.\n", EXIT_ERROR_MALLOC);
	fill_plane(scene, tokens, pl, ls);
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(pl);
		exit_with_lines(scene, ls, "Error: allocation failed for t_object.\n", EXIT_ERROR_MALLOC);
		//close_program(scene, "Error: allocation failed for t_object.\n", EXIT_ERROR_MALLOC);
	}
	//{
	//	free(pl);
	//	return (error_msg("allocation failed for t_object.", 1) && 0);
	//}
	obj->type = PLANE;
	obj->element = pl;
	obj->next = NULL;
	add_object(scene, obj);
	return (1);
}

static int	parse_fill_sphere(char **tokens, t_sphere *sp)
{
	char	**center;
	char	**color;
	
	center = NULL;
	color = NULL;
	center = ft_split(tokens[1], ',');
	color = ft_split(tokens[3], ',');
	if (!center || !color)
	{
		free_multiple_tab(2, center, color);
		return (error_msg("invalid sphere formatting", 1));
	}
	if (ft_count_size(center) != 3 || ft_count_size(color) != 3)
	{
		free_multiple_tab(2, center, color);
		return (error_msg("invalid sphere parameter number", 1));
	}
	sp->center.x = atof(center[0]);
	sp->center.y = atof(center[1]);
	sp->center.z = atof(center[2]);
	sp->radius = atof(tokens[2]) / 2.0;
	if (validate_assign_rgb(&sp->color, color))
	{
		free_multiple_tab(3, tokens, center, color);
		return (1);
	}
	free_multiple_tab(2, center, color);
	return (0);
}

int	parse_sphere(char **tokens, t_scene *scene, t_params *ls)
{
	t_sphere	*sp;

	if (ft_count_size(tokens) != 4)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: invalid sphere parameter number.\n", EXIT_ERROR_PARAM);
	}
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: allocation failed for t_sphere.\n", EXIT_ERROR_MALLOC);
	}
	if (parse_fill_sphere(tokens, sp))
	{
		free(sp);
		free_tab(tokens);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
		return (0);
	}
	if (!create_and_fill_obj(scene, SPHERE, sp))
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
	return (0);
}

static int	split_cy_fields(char **tokens, char ***center, char ***axis, char ***color)
{
	*center = NULL;
	*axis = NULL;
	*color = NULL;
	*center = ft_split(tokens[1], ',');
	*axis = ft_split(tokens[2], ',');
	*color = ft_split(tokens[5], ',');
	if (!(*center) || !(*axis) || !(*color))
	{
		free_multiple_tab(3, *center, *axis, *color);
		return (error_msg("invalid cylinder formatting.", 1));
	}
	if (ft_count_size(*center) != 3 || ft_count_size(*axis) != 3 || ft_count_size(*color) != 3)
	{
		free_multiple_tab(3, *center, *axis, *color);
		return (error_msg("invalid cylinder parameter size.", 1));
	}
	return (0);
}

static void	assign_cy_center_axis(t_cylinder *cy, char **center, char **axis)
{
	cy->centre.x = atof(center[0]);
	cy->centre.y = atof(center[1]);
	cy->centre.z = atof(center[2]);
	cy->axis.x = atof(axis[0]);
	cy->axis.y = atof(axis[1]);
	cy->axis.z = atof(axis[2]);
}

static int	assign_cy_dims(t_cylinder *cy, char **tokens)
{
	double	r;
	double	h;
	
	r = atof(tokens[3]) / 2.0;
	h = atof(tokens[4]);
	cy->radius = r;
	cy->height = h;
	if (r <= 0.0 || h <= 0.0)
		return (error_msg("cylinder radius/height must be positive.", 1));
	return (0);
}

static int	parse_fill_cylinder(char **tokens, t_cylinder *cy)
{
	char	**center;
	char	**axis;
	char	**color;
	
	center = NULL;
	axis = NULL;
	color = NULL;
	if (split_cy_fields(tokens, &center, &axis, &color))
		return (1);
	assign_cy_center_axis(cy, center, axis);
	if (normal_is_unit(cy->axis))
	{
		free_multiple_tab(3, center, axis, color);
		return (1);
	}
	if (assign_cy_dims(cy, tokens))
	{
		free_multiple_tab(3, center, axis, color);
		return (1);
	}
	if (validate_assign_rgb(&cy->color, color))
	{
		free_multiple_tab(3, center, axis, color);
		return (1);
	}
	free_multiple_tab(3, center, axis, color);
	return (0);
}

int	parse_cylinder(char **tokens, t_scene *scene, t_params *ls)
{
	t_cylinder	*cy;
	
	(void)ls;
	if (ft_count_size(tokens) != 6)
		return (error_msg("invalid cylinder parameter count", 1) && 0);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		return (error_msg("allocation failed for t_cylinder.", 1) && 0);
	if (parse_fill_cylinder(tokens, cy))
	{
		free(cy);
		return (0);
	}
	return (create_and_fill_obj(scene, CYLINDER, cy));
}
/*
//int	parse_plane(char **tokens, t_scene *scene)
//{
//	t_object	*obj;
//	t_plane		*pl;
//	char		**pos;
//	char		**normal;
//	char		**color;
//
//	if (!tokens[1] || !tokens[2] || !tokens[3])
//	{
//		ft_putstr_fd("Error.\nInvalid plane format.", 2);
//		return (0);
//	}
//	pl = malloc(sizeof(t_plane));
//	if (!pl)
//	{
//		ft_putstr_fd("Error.\nMalloc failed when creating plane.", 2);
//		return (0);
//	}
//	pos = ft_split(tokens[1], ',');
//	normal = ft_split(tokens[2], ',');
//	color = ft_split(tokens[3], ',');
//
//	if (!pos || !normal || !color)
//	{
//		ft_putstr_fd("Error.\nInvalid plane vector formatting.\n", 2);
//		if (pos)
//			free_tab(pos);
//		if (normal)
//			free_tab(normal);
//		if (color)
//			free_tab(color);
//		free(pl);
//		return (0);
//	}
//
//	pl->point.x = atof(pos[0]);
//	pl->point.y = atof(pos[1]);
//	pl->point.z = atof(pos[2]);
//
//	pl->normal.x = atof(normal[0]);
//	pl->normal.y = atof(normal[1]);
//	pl->normal.z = atof(normal[2]);
//
//	pl->color.r = ft_atoi(color[0]);
//	pl->color.g = ft_atoi(color[1]);
//	pl->color.b = ft_atoi(color[2]);
//
//	free_tab(pos);
//	free_tab(normal);
//	free_tab(color);
//
//	obj = malloc(sizeof(t_object));
//	if (!obj)
//	{
//		ft_putstr_fd("Error.\nMalloc failed for t_object.\n", 2);
//		free(pl);
//		return (0);
//	}
//	obj->type = PLANE;
//	obj->element = pl;
//	obj->next = NULL;
//	add_object(scene, obj);
//	return (1);
//}

//int	parse_sphere(char **tokens, t_scene *scene)
//{
//	t_object	*obj;
//	t_sphere	*sp;
//	char		**center;
//	char		**color;
//
//	if (!tokens[1] || !tokens[2] || !tokens[3])
//	{
//		ft_putstr_fd("Error.\nInvalid sphere format\n", 2);
//		return (0);
//	}
//	sp = malloc(sizeof(t_sphere));
//	if (!sp)
//	{
//		ft_putstr_fd("Error.\nFailed malloc for sphere.\n", 2);
//		return (0);
//	}
//	center = ft_split(tokens[1], ',');
//	color = ft_split(tokens[3], ',');
//	if (!center || !color)
//	{
//		ft_putstr_fd("Error.\nInvalid sphere formatting.\n", 2);
//		if (center)
//			free_tab(center);
//		if (color)
//			free_tab(color);
//		free (sp);
//		return (0);
//	}
//	sp->center.x = atof(center[0]);
//	sp->center.y = atof(center[1]);
//	sp->center.z = atof(center[2]);
//	sp->radius = atof(tokens[2]) / 2.0;
//	sp->color.r = ft_atoi(color[0]);
//	sp->color.g = ft_atoi(color[1]);
//	sp->color.b = ft_atoi(color[2]);
//
//	free_tab(center);
//	free_tab(color);
//	obj = malloc(sizeof(t_object));
//	if (!obj)
//	{
//		ft_putstr_fd("Error.\nFailed to malloc t_object.\n", 2);
//		free (sp);
//		return (0);
//	}
//	obj->type = SPHERE;
//	obj->element = sp;
//	obj->next = NULL;
//	add_object(scene, obj);
//	return (1);
//}

//int	parse_cylinder(char **tokens, t_scene *scene)
//{
//	t_object	*obj;
//	t_cylinder	*cy;
//	char		**center;
//	char		**axis;
//	char		**color;
//	double		radius;
//	double		height;
//
//	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
//	{
//		ft_putstr_fd("Error.\nInvalid cylinder format\n", 2);
//		return (0);
//	}
//	cy = malloc(sizeof(t_cylinder));
//	if (!cy)
//	{
//		ft_putstr_fd("Error.\nFailed malloc for cylinder.\n", 2);
//		return (0);
//	}
//	radius = atof(tokens[3]) / 2.0;
//	height = atof(tokens[4]);
//	cy->radius = radius;
//	cy->height = height;
//	center = ft_split(tokens[1], ',');
//	axis = ft_split(tokens[2], ',');
//	color = ft_split(tokens[5], ',');
//	if (!center || !axis || !color )//写个判断归一化向量范围的判断函数判断axis
//	{
//		ft_putstr_fd("Error.\nInvalid cylinder formatting.\n", 2);
//		if (center)
//			free_tab(center);
//		if (axis)
//			free_tab(axis);
//		if (color)
//			free_tab(color);
//		free (cy);
//		return (0);
//	}
//	cy->centre.x = atof(center[0]);
//	cy->centre.y = atof(center[1]);
//	cy->centre.z = atof(center[2]);
//
//	cy->axis.x = atof(axis[0]);
//	cy->axis.y = atof(axis[1]);
//	cy->axis.z = atof(axis[2]);
//
//	cy->color.r = ft_atoi(color[0]);
//	cy->color.g = ft_atoi(color[1]);
//	cy->color.b = ft_atoi(color[2]);
//
//	free_tab(center);
//	free_tab(axis);
//	free_tab(color);
//
//	obj = malloc(sizeof(t_object));
//	if (!obj)
//	{
//		ft_putstr_fd("Error.\nFailed to malloc t_object.\n", 2);
//		free (cy);
//		return (0);
//	}
//	obj->type = CYLINDER;
//	obj->element = cy;
//	obj->next = NULL;
//	add_object(scene, obj);
//	return (1);
//}*/
