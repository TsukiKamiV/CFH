/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:17:44 by luxu              #+#    #+#             */
/*   Updated: 2025/09/10 13:18:33 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	is_valid_key(const char *s)
{
	if (!s)
		return (0);
	if (ft_strcmp(s, "A") == 0)
		return (1);
	if (ft_strcmp(s, "C") == 0)
		return (1);
	if (ft_strcmp(s, "L") == 0)
		return (1);
	if (ft_strcmp(s, "sp") == 0)
		return (1);
	if (ft_strcmp(s, "pl") == 0)
		return (1);
	if (ft_strcmp(s, "cy") == 0)
		return (1);
	return (0);
}

int	line_has_illegal_character(char *line)
{
	char	**tokens;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (1);
	if (!tokens[0])
	{
		free_tab(tokens);
		return (1);
	}
	i = 1;
	while (tokens[i])
	{
		if (!is_valid_number_list(tokens[i]))
		{
			free_tab(tokens);
			return (1);
		}
		i++;
	}
	free_tab(tokens);
	return (0);
}

void	validate_scene_or_exit(t_scene *scene, t_params *ls)
{
	if (!scene->amb || !scene->cam || !scene->light)
		exit_with_lines(scene, ls, \
				"missing key element to create the scene.", \
				ERR_PARAM);
	if (!scene->objs)
		exit_with_lines(scene, ls, \
				"at least one object required.", \
				ERR_PARAM);
}

void	trim_newline(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
		{
			s[i] = '\0';
			break ;
		}
		i++;
	}
}

char	**read_file_with_gnl(int fd, char *line, char **tab)
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
