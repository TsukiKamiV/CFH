/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:40:10 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 14:42:08 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

static int	parse_cam_pos(t_scene *scene, char **tokens, \
		char ***pos, t_params *ls)
{
	*pos = ft_split(tokens[1], ',');
	if (!(*pos) || ft_count_size(*pos) != 3)
	{
		free_tab(*pos);
		exit_with_lines(scene, ls, \
				"invalid camera position formatting.", \
				ERR_PARAM);
	}
	scene->cam->pos.x = atof((*pos)[0]);
	scene->cam->pos.y = atof((*pos)[1]);
	scene->cam->pos.z = atof((*pos)[2]);
	return (0);
}

static int	parse_cam_orientation(t_scene *scene, char **tokens, \
		char ***orient, t_params *ls)
{
	t_vec3	tmp_orient;

	*orient = ft_split(tokens[2], ',');
	if (!(*orient) || ft_count_size(*orient) != 3)
	{
		free_tab(*orient);
		exit_with_lines(scene, ls, \
				"invalid camera orientation formatting.", \
				ERR_PARAM);
	}
	tmp_orient.x = atof((*orient)[0]);
	tmp_orient.y = atof((*orient)[1]);
	tmp_orient.z = atof((*orient)[2]);
	if (normal_is_unit(tmp_orient))
	{
		free_tab(*orient);
		exit_with_lines(scene, ls, \
				"camera orient must be normalized.", \
				ERR_PARAM);
	}
	scene->cam->orient = tmp_orient;
	return (0);
}

int	parse_camera(char **tokens, t_scene *scene, t_params *ls)
{
	char	**pos;
	char	**orient;
	double	tmp_fov;

	if (ft_count_size(tokens) != 4)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "invalid camera parameter number.", \
				ERR_PARAM);
	}
	scene->cam = malloc(sizeof(t_camera));
	if (!scene->cam)
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, "malloc failed for cam", ERR_MALLOC);
	}
	if (parse_cam_pos(scene, tokens, &pos, ls) || \
			parse_cam_orientation(scene, tokens, &orient, ls))
		return (1);
	tmp_fov = atof(tokens[3]);
	if (tmp_fov < 0.0 || tmp_fov > 180.0)
	{
		free_tab(tokens);
		free_multiple_tab(2, pos, orient);
		exit_with_lines(scene, ls, "camera FOV out of range", ERR_PARAM);
	}
	scene->cam->fov = tmp_fov;
	free_multiple_tab(2, pos, orient);
	return (0);
}
