/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:47 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 14:47:11 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

static int	parse_light_pos(t_scene *scene, char **tokens, char***pos, \
		t_params *ls)
{
	*pos = NULL;
	*pos = ft_split(tokens[1], ',');
	if (!(*pos))
	{
		free_multiple_tab(2, tokens, (*pos));
		exit_with_lines(scene, ls, \
				"Error: failed splitting light position parameter.\n", \
				EXIT_ERROR_PARAM);
	}
	if ((ft_count_size(*pos) != 3))
	{
		free_multiple_tab(2, tokens, (*pos));
		exit_with_lines(scene, ls, "Error: wrong light parameter number.\n", \
				EXIT_ERROR_PARAM);
	}
	return (0);
}

static int	parse_light_rgb(t_scene *scene, char **tokens, char***rgb, \
		t_params *ls)
{
	*rgb = NULL;
	*rgb = ft_split(tokens[3], ',');
	if (!(*rgb))
	{
		free_multiple_tab(2, tokens, (*rgb));
		exit_with_lines(scene, ls, \
				"Error: failed splitting light position parameter.\n", \
				EXIT_ERROR_PARAM);
	}
	if ((ft_count_size(*rgb) != 3))
	{
		free_multiple_tab(2, tokens, (*rgb));
		exit_with_lines(scene, ls, "Error: wrong light parameter number.\n", \
				EXIT_ERROR_PARAM);
	}
	return (0);
}

static void	assign_light_pos(t_light *light, char **pos)
{
	light->pos.x = atof(pos[0]);
	light->pos.y = atof(pos[1]);
	light->pos.z = atof(pos[2]);
}

static int	validate_light_ratio(char *s, double *out_ratio)
{
	double	val;

	val = strtod(s, NULL);
	if (val < 0.0 || val > 1.0)
		return (0);
	*out_ratio = val;
	return (1);
}

int	parse_light(char **tokens, t_scene *scene, t_params *ls)
{
	char	**pos;
	char	**rgb;
	double	ratio;

	if (ft_count_size(tokens) != 4)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: invalid light parameter number.\n", \
				EXIT_ERROR_PARAM);
	}
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: invalid light parameter number.\n", \
				EXIT_ERROR_PARAM);
	}
	parse_light_pos(scene, tokens, &pos, ls);
	parse_light_rgb(scene, tokens, &rgb, ls);
	assign_light_pos(scene->light, pos);
	if (!validate_light_ratio(tokens[2], &ratio))
	{
		free_multiple_tab(3, pos, rgb, tokens);
		exit_with_lines(scene, ls, "Error: light ratio out of range", \
				EXIT_ERROR_PARAM);
	}
	scene->light->ratio = ratio;
	if (validate_assign_rgb(&scene->light->color, rgb))
	{
		free_multiple_tab(3, pos, rgb, tokens);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
	}
	free_multiple_tab(2, pos, rgb);
	return (0);
}
