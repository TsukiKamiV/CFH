/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:28:25 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:20:51 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

static int	split_cy_fields(char **tokens, \
		char ***center, char ***axis, char ***color)
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
	if (ft_count_size(*center) != 3 || \
			ft_count_size(*axis) != 3 || ft_count_size(*color) != 3)
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

int	assign_cy_dims(t_cylinder *cy, char **tokens)
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
		return (error_msg("cylinder axis not normalized.", 1));
	}
	if (validate_cy_dims_and_color(cy, tokens, color))
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
		exit_with_lines(scene, ls, "cy param error", ERR_PARAM);
	}
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
	{
		free_tab (tokens);
		exit_with_lines(scene, ls, "cy malloc error", ERR_MALLOC);
	}
	if (parse_fill_cylinder(tokens, cy))
		cy_exit(scene, ls, tokens, cy);
	if (!create_and_fill_obj(scene, CYLINDER, cy))
		cy_exit(scene, ls, tokens, cy);
	return (0);
}
