/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:26:47 by luxu              #+#    #+#             */
/*   Updated: 2025/04/13 12:37:06 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*handle_single_philo(t_philo *philo, t_simulation *sim)
{
	pthread_mutex_lock(&sim->forks[0].mutex);
	print_status(philo, "has taken a fork");
	ft_usleep(sim->time_to_die + 1, sim);
	print_status(philo, "died");
	pthread_mutex_unlock(&sim->forks[0].mutex);
	return (NULL);
}

static void	run_philo_actions(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->sim_data;
	while (1)
	{
		if (check_sim_end(sim))
			break;
		if (!take_forks(philo))
			break;
		eat(philo);
		if (check_sim_end(sim))
			break;
		print_status(philo, "is sleeping");
		ft_usleep(sim->time_to_sleep, sim);
		if (check_sim_end(sim))
			break;
		ft_think(philo, 0);
	}
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation	*sim;

	philo = (t_philo *)arg;
	sim = philo->sim_data;
	if (sim->philo_num == 1)
		handle_single_philo(philo, sim);
	else
		run_philo_actions(philo);
	return (NULL);
}
//void	*routine(void *arg)
//{
//	t_philo			*philo;
//	t_simulation	*sim;
//
//	philo = (t_philo *)arg;
//	sim = philo->sim_data;
//	if (sim->philo_num == 1)
//		handle_single_philo(philo, sim);
//	else
//	{
//		while (1)
//		{
//			if (check_sim_end(sim) == true)
//				break ;
//			if (!take_forks(philo))
//				break ;
//			eat(philo);
//			if (check_sim_end(sim) == true)
//				break ;
//			print_status(philo, "is sleeping");
//			ft_usleep(sim->time_to_sleep, sim);
//			if (check_sim_end(sim) == true)
//				break ;
//			ft_think(philo, 0);
//		}
//	}
//	return (NULL);
//}
//
