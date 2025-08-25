/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_path_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:46:04 by luxu              #+#    #+#             */
/*   Updated: 2024/10/03 13:35:33 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	fill(char **tab, t_position size, t_position cur)
{
	if (cur.y < 0 || cur.y >= size.y || cur.x < 0 || cur.x >= size.x)
		return ;
	if (tab[cur.y][cur.x] != 'C' && tab[cur.y][cur.x] != 'P' \
			&& tab[cur.y][cur.x] != 'E' && tab[cur.y][cur.x] != '0')
		return ;
	tab[cur.y][cur.x] = 'F';
	fill(tab, size, (t_position){cur.x -1, cur.y});
	fill(tab, size, (t_position){cur.x + 1, cur.y});
	fill(tab, size, (t_position){cur.x, cur.y - 1});
	fill(tab, size, (t_position){cur.x, cur.y + 1});
}

void	flood_fill(char **tab, t_position size, t_position begin)
{
	fill(tab, size, begin);
}
