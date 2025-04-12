#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	t_simulation *sim;

	sim = philo->sim_data;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_relative_time(sim);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(sim->time_to_eat, sim);
	drop_forks(philo);
}
