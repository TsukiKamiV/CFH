/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:09:56 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 14:23:01 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*static void	calc_first_mode(t_philo *philo, int *first_mode, bool *right_first)
{
	t_simulation	*sim;

	sim = philo->sim_data;
	if ((sim->philo_num % 2 == 0 \
				&& philo->philo_id % 2 == 0) \
		|| (sim->philo_num % 2 != 0 \
			&& philo->philo_id % 2 == philo->eat_count % 2))
	{
		*right_first = true;
		*first_mode = 1;
	}
	else
	{
		*right_first = false;
		*first_mode = 2;
	}
}

static void	set_fork_order_by_right(t_philo *philo, \
		bool right_first, int *first_fork, int *second_fork)
{
	if (right_first)
	{
		*first_fork = philo->r_fork;
		*second_fork = philo->l_fork;
	}
	else
	{
		*first_fork = philo->l_fork;
		*second_fork = philo->r_fork;
	}
}*/

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

//bool	take_forks(t_philo *philo)
//{
//	t_simulation	*sim;
//	int				first_fork;
//	int				second_fork;
//	int				first_mode;
//	bool			right_first;
//
//	sim = philo->sim_data;
//	calc_first_mode(philo, &first_mode, &right_first);
//	set_fork_order_by_right(philo, right_first, &first_fork, &second_fork);
//	pthread_mutex_lock(&sim->forks[first_fork].mutex);
//	if (!check_end_unlock(sim, philo, first_mode))
//		return (false);
//	print_status(philo, "has taken a fork");
//	pthread_mutex_lock(&sim->forks[second_fork].mutex);
//	if (!check_end_unlock(sim, philo, 3))
//		return (false);
//	print_status(philo, "has taken a fork");
//	return (true);
//}

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
