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

void	*monitor_death_routine(void *arg)
{
	//每隔一小段时间（如0.5ms）循环一次
	//遍历所有哲学家
	int					i;
	t_simulation	*sim;
	t_philo			*philo;
	long			cur_time;
	
	sim = (t_simulation *)arg;
	while (1)
	{
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end == true)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			printf("DEBUG: philo[%ld] exiting loop at start due to sim_end\n", philo->philo_id);
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
			i++;
		}
		usleep(DEATH_MONITOR_SLICE);
	}
	return (NULL);
}
