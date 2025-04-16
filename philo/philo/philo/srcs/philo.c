/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:25:38 by luxu              #+#    #+#             */
/*   Updated: 2025/04/13 12:35:50 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	alloc_all(int argc, const char **argv, \
		t_simulation **sim, t_philo **philo)
{
	long	n;

	if (check_args(argc, argv, &n) == 0)
		return (1);
	if (check_time_params(argv) == false)
	{
		printf("Time params too large\n");
		return (1);
	}
	*sim = malloc(sizeof(t_simulation));
	if (!*sim)
		return (1);
	(*sim)->philo_num = (int)n;
	*philo = malloc(sizeof(t_philo) * (*sim)->philo_num);
	if (!*philo)
	{
		free_structs(NULL, *sim);
		return (1);
	}
	return (0);
}

static int	setup_all(t_simulation *sim, t_philo *philo, const char **argv)
{
	int	i;

	if (init_simulation(sim, argv, philo) == 1)
	{
		free_structs(philo, sim);
		return (1);
	}
	i = 0;
	while (i < sim->philo_num)
	{
		philo[i].sim_data = sim;
		i++;
	}
	if (init_philo(sim, philo) != 0)
	{
		free_structs(philo, sim);
		return (1);
	}
	return (0);
}

static int	init_all(int argc, const char **argv, \
		t_simulation **sim, t_philo **philo)
{
	if (alloc_all(argc, argv, sim, philo))
		return (1);
	if (setup_all(*sim, *philo, argv))
		return (1);
	return (0);
}

static void	join_threads(t_simulation *sim, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < sim->philo_num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	if (sim->philo_num > 1)
		pthread_join(sim->monitor_thread, NULL);
}

int	main(int argc, const char **argv)
{
	t_philo			*philo;
	t_simulation	*sim;

	if (init_all(argc, argv, &sim, &philo))
		return (1);
	if (sim->philo_num > 1)
		pthread_create(&sim->monitor_thread, NULL, monitor_sim_routine, sim);
	join_threads(sim, philo);
	free_structs(philo, sim);
	return (0);
}
