/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:18:08 by luxu              #+#    #+#             */
/*   Updated: 2024/10/03 12:18:36 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_position	ft_calculate_map_size(char **tab)
{
	t_position	size;

	size.y = (int)ft_strlen(*tab);
	size.x = 0;
	while (tab[size.x])
		size.x++;
	return (size);
}

int	ft_is_valid_item(char c)
{
	return (c == 'E' || c == 'P' || c == 'C' || c == '0' || c == '1');
}
