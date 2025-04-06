#include "../includes/philo.h"

//void	eat(t_philo *philo)
//{
//	t_simulation	*sim;
//
//	sim = philo->sim_data;
//	take_forks(philo);
//	pthread_mutex_lock(&philo->meal_mutex);
//	philo->last_meal_time = get_relative_time(sim);
//	philo->eat_count++;
//	pthread_mutex_unlock(&philo->meal_mutex);
//	print_status(philo, "is eating");
//	ft_usleep(sim->time_to_eat, sim);
//	drop_forks(philo);
//}

void	eat(t_philo *philo)
{
	t_simulation *sim;
	
	sim = philo->sim_data;
	pthread_mutex_lock(&sim->end_mutex);
	if (sim->sim_end == true)
	{
		printf("Debug: philo[%ld] sim ends before taking fork due to sim_end\n", philo->philo_id);
		pthread_mutex_unlock(&sim->end_mutex);
		return ;
	}
	pthread_mutex_unlock(&sim->end_mutex);
	take_forks(philo);
	pthread_mutex_lock(&sim->end_mutex);
	if (sim->sim_end == true)
	{
		pthread_mutex_unlock(&sim->end_mutex);
		drop_forks(philo); // 必须释放叉子，否则会死锁
		printf("Debug: philo[%ld] dropped forks due to sim_end before eating\n", philo->philo_id);
		return ;
	}
	pthread_mutex_unlock(&sim->end_mutex);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_relative_time(sim);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(sim->time_to_eat, sim);
	pthread_mutex_lock(&sim->end_mutex);
	if (sim->sim_end == false)
	{
		drop_forks(philo);
		printf("Debug: philo[%ld] dropped forks after eating\n", philo->philo_id);
	}
	pthread_mutex_unlock(&sim->end_mutex);
}
