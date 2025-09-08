/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_amb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:38:24 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 14:39:28 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
/**
 *ambient环境光参数：
 * A <ratio> <R.G.B>
 * ratio取值范围：0.0 ～ 1.0
 * rgb范围 0 ～ 255 （含）
 */

int	parse_ambient(char **tokens, t_scene *scene, t_params *ls)
{
	char	**rgb;

	scene->amb = malloc(sizeof(t_ambient));
	if (!scene->amb)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: memory allocation failed.\n", \
				EXIT_ERROR_MALLOC);
	}
	if (ft_count_size(tokens) != 3)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, \
				"Error: invalid ambient parameter number.\n", \
				EXIT_ERROR_PARAM);
	}
	scene->amb->ratio = strtod(tokens[1], NULL);
	if (scene->amb->ratio < 0.0 || scene->amb->ratio > 1.0)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "Error: ambient ratio out of range.\n", \
				EXIT_ERROR_PARAM);
	}
	rgb = ft_split(tokens[2], ',');
	if (validate_assign_rgb(&scene->amb->color, rgb))
	{
		free_multiple_tab(2, tokens, rgb);
		exit_with_lines(scene, ls, NULL, EXIT_ERROR_PARAM);
	}
	free_tab(rgb);
	return (0);
}
