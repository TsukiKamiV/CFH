/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:23:47 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 13:29:49 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static char	**read_file_with_gnl(int fd, char *line, char **tab)
{
	int	i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		tab[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	tab[i] = NULL;
	return (tab);
}

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
		return (0);
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
				"Error\n key element type error found in rt file.\n", \
				EXIT_ERROR_FILE);
	}
}

int	parse_scene_from_lines(t_params *ls, t_scene *scene)
{
	int		i;
	char	**tokens;

	if (all_lines_empty(ls))
		exit_with_lines(scene, ls, "Error\n empty rt file.\n", EXIT_ERROR_FILE);
	i = 0;
	while (i < ls->count)
	{
		if (!is_line_empty(ls->tab[i]))
		{
			if (line_has_illegal_character(ls->tab[i]))
				exit_with_lines(scene, ls, \
						"Error\n illegal character found in rt file.\n", \
						EXIT_ERROR_PARAM);
			tokens = ft_split(ls->tab[i], ' ');
			if (!tokens)
				return (0);
			if (!is_valid_key(tokens[0]))
			{
				free_tab(tokens);
				return (error_msg("key element type error", 1) && 0);
			}
			dispatch_element(tokens, scene, ls);
			free_tab(tokens);
		}
		i++;
	}
	validate_scene_or_exit(scene, ls);
	return (1);
}
