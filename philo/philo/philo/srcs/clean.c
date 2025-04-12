/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:53:05 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 12:53:12 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_simulation(t_simulation *sim, int flags)
{
	if (sim == NULL)
		return ;
	if ((flags & CLEAN_FORKS) && sim->forks)
		free (sim->forks);
	if (flags & CLEAN_END_MUTEX)
		pthread_mutex_destroy(&sim->end_mutex);
	if (flags & CLEAN_PRINT_MUTEX)
		pthread_mutex_destroy(&sim->print_mutex);
}
