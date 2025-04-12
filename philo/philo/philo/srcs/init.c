/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:13:50 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 14:23:28 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutexes(t_simulation *sim)
{
	int	flags;

	flags = 0;
	if (pthread_mutex_init(&sim->end_mutex, NULL) != 0)
		return (1);
	flags |= CLEAN_END_MUTEX;
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->end_mutex);
		return (1);
	}
	flags |= CLEAN_PRINT_MUTEX;
	sim->forks = malloc(sizeof(t_fork) * sim->philo_num);
	if (!sim->forks)
	{
		cleanup_simulation(sim, flags);
		return (1);
	}
	flags |= CLEAN_FORKS;
	if (init_forks_mutex(sim) == 1)
	{
		cleanup_simulation(sim, flags);
		return (1);
	}
	return (0);
}

int	init_simulation(t_simulation *sim, const char **argv, t_philo *philo)
{
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] && argv[5][0] != '\0')
		sim->number_of_times_to_eat = ft_atol(argv[5]);
	else
		sim->number_of_times_to_eat = -1;
	sim->sim_end = false;
	sim->full_philos = 0;
	sim->start_time = get_current_time();
	sim->philo_array = philo;
	if (init_mutexes(sim) != 0)
		return (1);
	return (0);
}

int	init_philo(t_simulation *sim, t_philo *philo)
{
	int	i;

	if (!philo)
		return (0);
	i = 0;
	while (i < sim->philo_num)
	{
		philo[i].philo_id = i + 1;
		philo[i].last_meal_time = 0;
		philo[i].eat_count = 0;
		philo[i].sim_data = sim;
		philo[i].l_fork = i;
		philo[i].r_fork = (i + 1) % sim->philo_num;
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL) != 0)
			return (1);
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
		{
			while (--i >= 0)
			{
				pthread_join(philo[i].thread, NULL);
				pthread_mutex_destroy(&philo[i].meal_mutex);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_forks_mutex(t_simulation *sim)
{
	int	i;
	int	j;

	i = 0;
	while (i < sim->philo_num)
	{
		if (pthread_mutex_init(&sim->forks[i].mutex, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&sim->forks[j].mutex);
				j++;
			}
			free (sim->forks);
			pthread_mutex_destroy(&sim->end_mutex);
			pthread_mutex_destroy(&sim->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
