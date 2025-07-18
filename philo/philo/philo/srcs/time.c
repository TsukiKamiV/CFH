/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:28:18 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 14:29:31 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	get_relative_time(t_simulation *sim)
{
	return (get_current_time() - sim->start_time);
}

void	ft_usleep(long duration_ms, t_simulation *sim)
{
	long	start;
	long	now;

	start = get_relative_time(sim);
	while (1)
	{
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end == true)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			return ;
		}
		pthread_mutex_unlock(&sim->end_mutex);
		now = get_relative_time(sim);
		if ((now - start) >= duration_ms)
			return ;
		usleep(SLEEP_SLICE);
	}
}

/*
 ** Multiplié par 2 : cela sert à indiquer la fenêtre de concurrence lorsque
 ** deux philosophes adjacents envisagent de manger en même temps.
 ** Soustraire le temps de sommeil : puisque le sommeil occupe une partie
 ** de cette fenêtre, il faut la retirer.
 ** Facteur de réglage : il permet d'éviter un délai excessif, de s'assurer
 ** que le processus global ne soit pas perturbé et contribue à désynchroniser
 ** les actions.
 */
void	ft_think(t_philo *philo, int befor_begin)
{
	long	time_to_think;

	time_to_think = 0;
	if (!befor_begin)
		print_status(philo, "is thinking");
	if (philo->sim_data->philo_num % 2 != 0)
	{
		time_to_think = (philo->sim_data->time_to_eat * 2) \
				- philo->sim_data->time_to_sleep;
		if (time_to_think < 0)
			time_to_think = 0;
		ft_usleep(time_to_think * 0.42, philo->sim_data);
	}
}
