#include "../includes/philo.h"

/**
 *在C语言线程库中，线程函数的返回值必须是一个void *类型。
 *pthread库的线程函数prototype为 void *(*start_routine)(void * )
 *即：函数接受一个void *作为参数，用于传递任意数据
 *函数返回一个void *值用于返回任意数据
 */

void	*handle_single_philo(t_philo *philo, t_simulation *sim)
{
	//尝试获取唯一的叉子
	pthread_mutex_lock(&sim->forks[0].mutex);
	//打印拿叉子的动作（此时桌上只有一把叉子，无法进食）
	print_status(philo, "has taken a fork");
	//等待饿死时间
	usleep(sim->time_to_die * 1000);//用ft_sleep函数替换？需确认输出要求秒还是毫秒
	//打印死亡
	print_status(philo, "died");
	//解除互斥锁
	pthread_mutex_unlock(&sim->forks[0].mutex);
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
		if (philo->eat_count >= sim->number_of_times_to_eat)
			count++;
		else
			return (false);
		i++;
	}
	pthread_mutex_lock(&sim->end_mutex);
	if (!sim->sim_end)
	{
		//printf("%ld %li died\n", cur_time, philo->philo_id);
		print_status(philo, "All philos have eaten enough");// 待定
		sim->sim_end = true;
	}
	pthread_mutex_unlock(&sim->end_mutex);
	return (true);
}

void	take_fork(t_philo *philo, t_simulation *sim)
{
	//if (philo->philo_id % 2 == 0)//偶数🆔
	//{
	//	if (pthread_mutex_lock(&sim->forks[philo->l_fork].mutex) != 0)
	//
	//}
}

void	change_status(t_philo *philo, t_simulation *sim)
{
	if (philo->state == THINKING)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		philo->eat_count++;
		philo->state = EATING;
		pthread_mutex_unlock(&philo->meal_mutex);
		print_status(philo, "is eating");//里面有print_mutex保护
	}
	if (philo->state == EATING)
	{
		
	}
}

void	*handle_multiple_philo(t_philo *philo, t_simulation *sim)
{
	long	cur_time;
	int		i;
	
	while (!sim->sim_end)
	{
		cur_time = get_relative_time(sim);//cur_time应该在循环外设置还是在kill里面？？
		//如果cur_time超过了当前哲学家的time_to_die，杀死该philo，返回
		if (kill_philo(philo, sim, cur_time) == 1)
			continue;//应该break还是continue?（kill函数已经将sim_end设置为true）
		if (sim->number_of_times_to_eat > 0)//应该在外面遍历所有philo并检查是否都达到次数？
		{
			if (everybody_is_full(philo, sim))
				continue;
			else
				break;
		}
		//没有人死掉， 或有且没达到最少进食次数，或没有最少进食次数
		//拿叉子 （根据人数奇偶）
		i = 0;
		while (i < sim->philo_num)
		{
			//take_fork(&philo[i], sim);
			philo[i].state = THINKING;
			if (pthread_mutex_lock(&sim->forks[philo[i].l_fork].mutex) == 0)
			{
				print_status(&philo[i], "has taken a fork");
				pthread_mutex_unlock(&sim->forks[philo[i].l_fork].mutex);
			}
			if (pthread_mutex_lock(&sim->forks[philo[i].r_fork].mutex) == 0)
			{
				print_status(&philo[i], "has taken a fork");
				pthread_mutex_unlock(&sim->forks[philo[i].r_fork].mutex);
			}
			
			}
			
		}
		
		
	}
	return (NULL);
}


void	*routine(void *arg)
{
	t_philo			*philo;
	t_simulation 	*sim;
	//long			cur_time;
	
	philo = (t_philo *)arg;
	sim = philo->sim_data;
	if (sim->philo_num == 1)
		handle_single_philo(philo, sim);
	else
		handle_multiple_philo(philo, sim);
	//while (!sim->sim_end)
	//{
	//	cur_time = get_relative_time(sim);
	//	if (cur_time - philo->last_meal_time >= sim->time_to_die)//如果当前时间减去最后一次吃饭时间长于饿死时间
	//	{
	//		//触发死亡逻辑
	//		pthread_mutex_lock(&sim->end_mutex);
	//		if (!sim->sim_end)
	//		{
	//			printf("%ld %li died\n", cur_time, philo->philo_id);
	//			sim->sim_end = true;
	//		}
	//		pthread_mutex_unlock(&sim->end_mutex);
	//		return (NULL);
	//	}
	//
	//	pthread_mutex_lock(&philo->sim_data->end_mutex);
	//	if (philo->sim_data->sim_end)
	//	{
	//		pthread_mutex_unlock(&philo->sim_data->end_mutex);
	//		break;
	//	}
	//	pthread_mutex_unlock(&philo->sim_data->end_mutex);
	//
	//	printf("Philosopher %li has eaten.\n", philo->philo_id);
	//	usleep((unsigned int)philo->sim_data->time_to_eat);
	//	printf("Philosopher %li has finished eating.\n", philo->philo_id);
	//	printf("Philosopher %li is sleeping.\n", philo->philo_id);
	//	usleep((unsigned int)philo->sim_data->time_to_sleep);
	//	//usleep(1000000); // Simulate sleeping (1 second)
	//
	//	// Thinking
	//	printf("Philosopher %li is thinking.\n", philo->philo_id);
	//	usleep(100000); // Simulate thinking (1 second)
	//}
	return (NULL);
}
