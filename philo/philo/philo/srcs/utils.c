/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:29:54 by luxu              #+#    #+#             */
/*   Updated: 2025/04/13 12:34:56 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_philo_struct(t_philo *philo, long philo_num)
{
	int	i;

	if (philo)
	{
		i = 0;
		while (i < philo_num)
		{
			pthread_mutex_destroy(&philo[i].meal_mutex);
			i++;
		}
		free (philo);
	}
}

void	free_structs(t_philo *philo, t_simulation *sim)
{
	int	i;

	free_philo_struct(philo, sim->philo_num);
	if (sim)
	{
		if (sim->forks)
		{
			i = 0;
			while (i < sim->philo_num)
			{
				pthread_mutex_destroy(&sim->forks[i].mutex);
				i++;
			}
			free (sim->forks);
		}
	}
	pthread_mutex_destroy(&sim->print_mutex);
	free (sim);
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	if (ft_strcmp(status, "Everybody is full!") != 0)
		printf("%ld %li %s\n", get_relative_time(philo->sim_data), \
				philo->philo_id, status);
	else
		printf("%ld %s\n", get_relative_time(philo->sim_data), status);
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
}
