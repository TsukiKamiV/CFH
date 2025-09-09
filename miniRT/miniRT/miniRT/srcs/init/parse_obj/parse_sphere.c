/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:36:31 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 14:37:17 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

static void	assign_sp_tabs(t_sphere *sp, char **center, char **tokens)
{
	sp->center.x = atof(center[0]);
	sp->center.y = atof(center[1]);
	sp->center.z = atof(center[2]);
	sp->radius = atof(tokens[2]) / 2.0;
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
	assign_sp_tabs(sp, center, tokens);
	if (validate_assign_rgb(&sp->color, color))
	{
		free_multiple_tab(2, center, color);
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
		exit_with_lines(scene, ls, "wrong number: sp", ERR_PARAM);
	}
	sp = malloc(sizeof(t_sphere));
	if (!sp)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "malloc failed: sp", ERR_MALLOC);
	}
	if (parse_fill_sphere(tokens, sp))
	{
		free(sp);
		free_tab(tokens);
		exit_with_lines(scene, ls, NULL, ERR_PARAM);
	}
	if (!create_and_fill_obj(scene, SPHERE, sp))
	{
		free_tab(tokens);
		free (sp);
		exit_with_lines(scene, ls, NULL, ERR_PARAM);
	}
	return (0);
}
