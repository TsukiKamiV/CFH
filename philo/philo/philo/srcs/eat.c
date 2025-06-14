/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:09:20 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 13:09:44 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	t_simulation	*sim;

	sim = philo->sim_data;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_relative_time(sim);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(sim->time_to_eat, sim);
	drop_forks(philo);
}
