/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:09:56 by luxu              #+#    #+#             */
/*   Updated: 2025/04/16 13:44:50 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_end_unlock(t_simulation *sim, t_philo *philo, int mode)
{
	pthread_mutex_lock(&sim->end_mutex);
	if (sim->sim_end)
	{
		if (mode == 1)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
			return (false);
		}
		else if (mode == 2)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
			return (false);
		}
		else if (mode == 3)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			drop_forks(philo);
			return (false);
		}
	}
	pthread_mutex_unlock(&sim->end_mutex);
	return (true);
}

bool	take_forks(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->sim_data;
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(&sim->forks[philo->r_fork].mutex);
		if (!check_end_unlock(sim, philo, 1))
			return (false);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&sim->forks[philo->l_fork].mutex);
		if (!check_end_unlock(sim, philo, 3))
			return (false);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&sim->forks[philo->l_fork].mutex);
		if (!check_end_unlock(sim, philo, 2))
			return (false);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&sim->forks[philo->r_fork].mutex);
		if (!check_end_unlock(sim, philo, 3))
			return (false);
		print_status(philo, "has taken a fork");
	}
	return (true);
}

void	drop_forks(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->sim_data;
	pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
	pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
}
