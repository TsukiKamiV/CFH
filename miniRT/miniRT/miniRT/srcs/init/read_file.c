/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:23:47 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:19:26 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	load_lines_into_tab(const char *filename, char ***out_tab, int count)
{
	int		fd;
	char	**tab;
	char	*line;

	if (!filename || !out_tab || count < 0)
		return (0);
	*out_tab = NULL;
	line = NULL;
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (error_msg("malloc failed", 0));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(tab);
		return (0);
	}
	*out_tab = read_file_with_gnl(fd, line, tab);
	return (1);
}

int	read_all_lines(const char *filename, t_params *params)
{
	int		ok;
	int		count;
	char	**tab;

	if (!params)
		return (0);
	params->tab = NULL;
	params->count = 0;
	ok = count_lines_in_file(filename, &count);
	if (!ok)
		return (0);
	ok = load_lines_into_tab(filename, &tab, count);
	if (!ok)
		return (0);
	params->tab = tab;
	params->count = count;
	return (1);
}

void	dispatch_element(char **tokens, t_scene *scene, t_params *ls)
{
	if (ft_strcmp(tokens[0], "A") == 0 && !scene->amb)
		parse_ambient(tokens, scene, ls);
	else if (ft_strcmp(tokens[0], "C") == 0 && !scene->cam)
		parse_camera(tokens, scene, ls);
	else if (ft_strcmp(tokens[0], "L") == 0 && !scene->light)
		parse_light(tokens, scene, ls);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		parse_sphere(tokens, scene, ls);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		parse_plane(tokens, scene, ls);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		parse_cylinder(tokens, scene, ls);
	else
	{
		free_tab(tokens);
		exit_with_lines(scene, ls, \
				"wrong element type\n", ERR_FILE);
	}
}

int	process_line(t_scene *scene, t_params *ls, char *s)
{
	char	**tokens;

	if (line_has_illegal_character(s))
		exit_with_lines(scene, ls, "illegal characters", ERR_PARAM);
	tokens = ft_split(s, ' ');
	if (!tokens)
		return (0);
	if (!is_valid_key(tokens[0]))
	{
		free_tab(tokens);
		return (error_msg("wrong element type", 1) && 0);
	}
	dispatch_element(tokens, scene, ls);
	free_tab(tokens);
	return (1);
}

int	parse_scene_from_lines(t_params *ls, t_scene *scene)
{
	int		i;

	if (all_lines_empty(ls))
		exit_with_lines(scene, ls, "empty rt file", ERR_FILE);
	i = 0;
	while (i < ls->count)
	{
		if (!is_line_empty(ls->tab[i]))
			if (!process_line(scene, ls, ls->tab[i]))
				return (0);
		i++;
	}
	validate_scene_or_exit(scene, ls);
	return (1);
}
