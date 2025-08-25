/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:05:25 by luxu              #+#    #+#             */
/*   Updated: 2024/10/05 14:08:44 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

#if defined(__linux__)

void	destroy_display(void *mlx_ptr)
{
	mlx_destroy_display(mlx_ptr);
}

#else

void	destroy_display(void *mlx_ptr)
{
}

#endif
