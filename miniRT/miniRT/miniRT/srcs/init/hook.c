/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:19:54 by luxu              #+#    #+#             */
/*   Updated: 2025/09/08 13:20:10 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_EXIT || keycode == KEY_QUIT)
		close_program(scene, NULL, EXIT_SUCCESS_KEY);
	return (0);
}
