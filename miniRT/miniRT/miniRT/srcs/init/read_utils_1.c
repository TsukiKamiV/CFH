/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:11:11 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 14:12:10 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	count_lines_in_file(const char *filename, int *out_count)
{
	int		fd;
	char	*line;
	int		count;

	if (!filename || !out_count)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_msg("cannot open file", 0));
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
	*out_count = count;
	return (1);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	all_lines_empty(t_params *ls)
{
	int	i;

	if (!ls || ls->count == 0 || !ls->tab)
		return (1);
	i = 0;
	while (i < ls->count)
	{
		if (!is_line_empty(ls->tab[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_number_segment(const char *t, int *pi)
{
	int	i;
	int	digits;
	int	frac;

	i = *pi;
	digits = 0;
	frac = 0;
	if (t[i] == '+' || t[i] == '-')
		i++;
	while (ft_isdigit(t[i]))
	{
		digits++;
		i++;
	}
	i = scan_frac(t, i, &frac);
	if (digits + frac == 0)
		return (0);
	*pi = i;
	return (1);
}

int	is_valid_number_list(const char *t)
{
	int	i;
	int	ok;

	i = 0;
	if (!t || !*t)
		return (0);
	while (t[i])
	{
		ok = parse_number_segment(t, &i);
		if (!ok)
			return (0);
		if (t[i] == '\0')
			return (1);
		if (t[i] != ',' || t[i + 1] == '\0')
			return (0);
		i++;
	}
	return (1);
}
