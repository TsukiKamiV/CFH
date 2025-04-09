#include "../includes/philo.h"

/**
 *哲学家根据编号（奇偶）决定拿叉子的顺序
 *加锁对应的叉子
 *打印拿叉子
 *吃完后按顺序解锁两把叉子
 */
//奇数/偶数id的philo拿起叉子的顺序不同；
//奇数🆔先拿左🍴
//偶数🆔先拿右🍴
//可以避免死锁并改善先发性
//还可以在偶数🆔的routine开始之前加1毫秒延时，进一步减少争用

bool	take_forks(t_philo *philo, bool *has_left, bool *has_right)
{
	t_simulation	*sim;
	bool			right_first;
	
	sim = philo->sim_data;
	*has_left = false;
	*has_right = false;
	
	if (sim->philo_num % 2 == 0)
		right_first = (philo->philo_id % 2 == 0);
	else
		right_first = (philo->philo_id % 2 == philo->eat_count % 2);
	
	if (right_first)
	{
		pthread_mutex_lock(&sim->forks[philo->r_fork].mutex);
		*has_right = true;

		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			//pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
			//*has_right = false;
			return (false);
		}
		pthread_mutex_unlock(&sim->end_mutex);
		print_status(philo, "has taken right fork");
		
		pthread_mutex_lock(&sim->forks[philo->l_fork].mutex);
		*has_left = true;
		
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			//pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
			//pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
			//*has_right = false;
			//*has_left = false;
			return (false);
		}
		pthread_mutex_unlock(&sim->end_mutex);
		print_status(philo, "has taken left fork");
	}
	else
	{
		pthread_mutex_lock(&sim->forks[philo->l_fork].mutex);
		*has_left = true;
		
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			//pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
			//*has_left = false;
			return (false);
		}
		pthread_mutex_unlock(&sim->end_mutex);
		print_status(philo, "has taken left fork");
		
		pthread_mutex_lock(&sim->forks[philo->r_fork].mutex);
		*has_right = true;
		
		pthread_mutex_lock(&sim->end_mutex);
		if (sim->sim_end)
		{
			pthread_mutex_unlock(&sim->end_mutex);
			//pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
			//pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
			//*has_right = false;
			//*has_left = false;
			return (false);
		}
		pthread_mutex_unlock(&sim->end_mutex);
		print_status(philo, "has taken right fork");
	}
	return true;
}

void	drop_forks(t_philo *philo)
{
	t_simulation	*sim;
	
	sim = philo->sim_data;
	//if (philo->philo_id % 2 == 0)
	//{
	//	pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
	//	pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
	//}
	//else
	//{
	pthread_mutex_unlock(&sim->forks[philo->l_fork].mutex);
	pthread_mutex_unlock(&sim->forks[philo->r_fork].mutex);
	//}
}
