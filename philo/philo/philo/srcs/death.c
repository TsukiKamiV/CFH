#include "../includes/philo.h"
/**
 *@return 0->not dead; 1 -> dead
 */

int	kill_philo(t_philo *philo, t_simulation *sim, long cur_time)
{
	if (cur_time - philo->last_meal_time >= sim->time_to_die)
	{
		pthread_mutex_lock(&sim->end_mutex);
		if (!sim->sim_end)
		{
			//printf("%ld %li died\n", cur_time, philo->philo_id);
			print_status(philo, "died");
			sim->sim_end = true;
		}
		pthread_mutex_unlock(&sim->end_mutex);
		return (1);
	}
	return (0);
}
