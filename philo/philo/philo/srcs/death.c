#include "../includes/philo.h"
/**
 *@return 0->not dead; 1 -> dead
 */

int	kill_philo(t_philo *philo, t_simulation *sim, long cur_time)
{
	int	need_print;//在开闭sim->end_mutex的时候，不调用print_status并同时开闭print_mutex，避免嵌套锁
	
	need_print = 0;
	if (cur_time - philo->last_meal_time > sim->time_to_die)
	{
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end == false)
		{
			need_print = true;
			sim->sim_end = true;
		}
		pthread_mutex_unlock(&sim->end_mutex);
		if (need_print)
			print_status(philo, "died");
		return (1);
	}
	return (0);
}

void	*monitor_sim_routine(void *arg)
{
	int					i;
	t_simulation	*sim;
	t_philo			*philo;
	long			cur_time;

	sim = (t_simulation *)arg;
	while (sim->philo_num > 1 && 1)
	{
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end == true)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			//printf("DEBUG: philo[%ld] exiting loop at start due to sim_end\n", philo->philo_id);
			break;
		}
		pthread_mutex_unlock(&sim->end_mutex);
		i = 0;
		while (i < sim->philo_num)
		{
			philo = &sim->philo_array[i];
			cur_time = get_relative_time(sim);
			if (kill_philo(philo, sim, cur_time) != 0)
				return (NULL);
			if (sim->number_of_times_to_eat > 0 && everybody_is_full(sim->philo_array, sim))
				return (NULL);
			i++;
		}
		usleep(DEATH_MONITOR_SLICE);
	}
	return (NULL);
}

bool	everybody_is_full(t_philo *philo, t_simulation *sim)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < sim->philo_num)
	{
		if (philo[i+1].eat_count >= sim->number_of_times_to_eat)
			count++;
		else
		{
			(void)count;
			return (false);
		}
		i++;
	}
	pthread_mutex_lock(&sim->end_mutex);
	if (sim->sim_end == false)
		sim->sim_end = true;
	pthread_mutex_unlock(&sim->end_mutex);
	print_status(philo, "Everybody is full!");
	return (true);
}
