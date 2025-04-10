#include "../includes/philo.h"

/**
 *在C语言线程库中，线程函数的返回值必须是一个void *类型。
 *pthread库的线程函数prototype为 void *(*start_routine)(void * )
 *即：函数接受一个void *作为参数，用于传递任意数据
 *函数返回一个void *值用于返回任意数据
 */

void	*handle_single_philo(t_philo *philo, t_simulation *sim)
{
	pthread_mutex_lock(&sim->forks[0].mutex);
	print_status(philo, "has taken a fork");
	ft_usleep(sim->time_to_die + 1, sim, false);
	print_status(philo, "died");
	pthread_mutex_unlock(&sim->forks[0].mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation 	*sim;
	
	philo = (t_philo *)arg;
	sim = philo->sim_data;
	if (sim->philo_num == 1)
		handle_single_philo(philo, sim);
	
	else
	{
		while (1)
		{
			pthread_mutex_lock(&sim->end_mutex);
			if (sim->sim_end)
			{
				pthread_mutex_unlock(&sim->end_mutex);
				//printf("DEBUG: philo[%ld] exiting loop at start due to sim_end\n", philo->philo_id);
				break;
			}
			pthread_mutex_unlock(&sim->end_mutex);
			if (!take_forks(philo))
				break;
			eat(philo);
			//printf("DEBUG: philo[%ld] exit eating (for x reason) at time %ld\n", philo->philo_id, get_relative_time(sim));
			pthread_mutex_lock(&sim->end_mutex);
			if (sim->sim_end)
			{
				pthread_mutex_unlock(&sim->end_mutex);
				//printf("DEBUG: philo[%ld] exiting loop after eating due to sim_end\n", philo->philo_id);
				break;
			}
			pthread_mutex_unlock(&sim->end_mutex);
			//printf("DEBUG: philo[%ld] starting to sleep at time %ld\n", philo->philo_id, get_relative_time(sim));
			if (sim->sim_end)
			{
				pthread_mutex_unlock(&sim->end_mutex);
				//printf("DEBUG: philo[%ld] didn't start sleeping due to sim_end\n", philo->philo_id);
				break;
			}
			print_status(philo, "is sleeping");
			ft_usleep(sim->time_to_sleep, sim, false);
			//printf("DEBUG: philo[%ld] finished (or stopped) sleeping at time %ld\n", philo->philo_id, get_relative_time(sim));
			pthread_mutex_lock(&sim->end_mutex);
			if (sim->sim_end)
			{
				pthread_mutex_unlock(&sim->end_mutex);
				//printf("DEBUG: philo[%ld] exiting loop after sleeping due to sim_end\n", philo->philo_id);
				break;
			}
			pthread_mutex_unlock(&sim->end_mutex);
			//printf("DEBUG: philo[%ld] starting to think at time %ld\n", philo->philo_id, get_relative_time(sim));
			//print_status(philo, "is thinking");
			ft_think(philo, 0);
		}
		//printf("DEBUG: philo[%ld] exiting routine at time %ld\n", philo->philo_id, get_relative_time(sim));
	}
	return (NULL);
}
/**
 *[循环开始]
 |
 |--- 检查 sim_end，是否已有哲学家死亡
 |
 |--- 判断奇偶
 |       |-- 奇数：拿左 -> 拿右
 |       |-- 偶数：usleep(1ms) -> 拿右 -> 拿左
 |
 |--- 拿到两把叉子？
 |       |-- 是：检查是否饿死//monitor_death
 |       |       |-- 没死：更新last_meal_time，状态 eating
 |       |       |-- 死了：打印死亡，结束线程
 |
 |--- usleep(time_to_eat)
 |
 |--- 按照顺序释放叉子
 |
 |--- 状态 sleeping -> usleep(time_to_sleep)
 |
 |--- 状态 thinking
 |
 [下一轮循环]
 */
