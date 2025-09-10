/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:42:47 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:23:46 by luxu             ###   ########.fr       */
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
				"failed splitting light position parameter", \
				ERR_PARAM);
	}
	if ((ft_count_size(*pos) != 3))
	{
		free_multiple_tab(2, tokens, (*pos));
		exit_with_lines(scene, ls, "wrong light parameter number", \
				ERR_PARAM);
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
				"failed splitting light position parameter", \
				ERR_PARAM);
	}
	if ((ft_count_size(*rgb) != 3))
	{
		free_multiple_tab(2, tokens, (*rgb));
		exit_with_lines(scene, ls, "wrong light parameter number", \
				ERR_PARAM);
	}
	return (0);
}

static void	assign_light_pos(t_light *light, char **pos)
{
	light->pos.x = atof(pos[0]);
	light->pos.y = atof(pos[1]);
	light->pos.z = atof(pos[2]);
}

static int	validate_light_ratio(char **tokens, char **pos, \
		char **rgb, t_scene *scene)
{
	double	tmp_ratio;

	tmp_ratio = strtod(tokens[2], NULL);
	if (tmp_ratio < 0.0 || tmp_ratio > 1.0)
	{
		free_multiple_tab(3, tokens, rgb, pos);
		return (0);
	}
	scene->light->ratio = tmp_ratio;
	return (1);
}

int	parse_light(char **tokens, t_scene *scene, t_params *ls)
{
	char	**pos;
	char	**rgb;

	check_light_size(tokens, scene, ls);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "malloc failed: light", ERR_MALLOC);
	}
	parse_light_pos(scene, tokens, &pos, ls);
	parse_light_rgb(scene, tokens, &rgb, ls);
	assign_light_pos(scene->light, pos);
	if (!validate_light_ratio(tokens, pos, rgb, scene))
		exit_with_lines(scene, ls, "wrong light ratio", ERR_PARAM);
	if (validate_assign_rgb(&scene->light->color, rgb))
	{
		free_multiple_tab(3, pos, rgb, tokens);
		exit_with_lines(scene, ls, NULL, ERR_PARAM);
	}
	free_multiple_tab(2, pos, rgb);
	return (0);
}
