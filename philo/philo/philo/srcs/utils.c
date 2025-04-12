/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:29:54 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 14:31:03 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_structs(t_philo *philo, t_simulation *sim)
{
	int	i;

	if (philo)
	{
		i = 0;
		while (i < sim->philo_num)
		{
			pthread_mutex_destroy(&philo[i].meal_mutex);
			i++;
		}
		free (philo);
	}
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
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
