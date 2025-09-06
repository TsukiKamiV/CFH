#include "../../../includes/miniRT.h"

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
		return (error_msg("cylinder axis vector must be normalized.", 1));
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
	
	if (ft_count_size(tokens) != 6)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: invalid cylinder parameter number", EXIT_ERROR_PARAM);
	}
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
	{
		free (tokens);
		exit_with_lines(scene, ls, "Error: allocation failed for t_cylinder.\n", EXIT_ERROR_MALLOC);
	}
	if (parse_fill_cylinder(tokens, cy))
	{
		free(cy);
		free_tab(tokens);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
		
	}
	if (!create_and_fill_obj(scene, CYLINDER, cy))
	{
		free_tab(tokens);
		free (cy);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
	}
	return (0);
}
