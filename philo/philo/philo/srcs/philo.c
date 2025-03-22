//
//  Created by Luyao Xu on 18/12/2024.
//

#include "../includes/philo.h"

/**
 *@param number_of_philosophers time_to_die  time_to_eat  time_to_sleep   [number_of_times_each_philosopher_must_eat]
 *number_of_philosophers: The number of philosophers and also the number of forks.
 ◦ time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
 ◦ time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
 ◦ time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
 ◦ number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
 *
 * Each philosopher has a number ranging from 1 to number_of_philosophers.
 • Philosopher number 1 sits next to philosopher number number_of_philosophers. Any other philosopher number N sits between philosopher number N - 1 and philoso- pher number N + 1.
 *
 * About the logs of your program:
 • Any state change of a philosopher must be formatted as follows:
 ◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
 ◦ timestamp_in_ms X is sleeping
 ◦ timestamp_in_ms X is thinking
 ◦ timestamp_in_ms X died
 Replace timestamp_in_ms with the current timestamp in milliseconds
 and X with the philosopher number.
 • A displayed state message should not be mixed up with another message.
 • A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
 *
 *
 *
 * External funcs:
 * memset, printf, malloc, free, write,
 usleep, gettimeofday, pthread_create,
 pthread_detach, pthread_join, pthread_mutex_init,
 pthread_mutex_destroy, pthread_mutex_lock,
 pthread_mutex_unlock
 */

int main(int argc, const char **argv)
{
	int				i;
	long			n;
	t_philo			*philo;
	//t_fork			*forks;
	t_simulation	*sim;
	
	//检查参数个数，以及输入是否合法（数字）
	//TODO:检查输入的大小限制
	if (check_args(argc, argv) == 0)
		return (1);
	//先初始化全局控制结构，录入全局共享参数
	//分配sim的内存
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (1);
	//在外部直接把第一个参数设置为哲学家人数（全局使用）
	n = ft_atol(argv[1]);
	if (n <= 0 || n > INT_MAX)
	{
		printf("Invalid philosopher number\n");
		return (1);
	}
	sim->philo_num = (int)n;
	//初始化simulation中其他的变量，如果初始化失败直接结束程序
	if (init_simulation(sim, argv) == 1)
	{
		free (sim);
		return (1);
	}
	
	philo = malloc(sizeof(t_philo) * sim->philo_num);
	//forks = malloc(sizeof(t_fork) * sim->philo_num);
	if (!philo)
	{
		free_structs(philo, sim);
		return (1);
	}
	i = 0;
	while (i < sim->philo_num)
	{
		philo[i].sim_data = sim;
		i++;
	}
	//routine的调用在init_philo里面，易读性太差，需要拿出来。但要确保内存释放
	if (init_philo(sim, philo, sim->start_time) != 0)
	{
		free_structs(philo, sim);
		return (1);
	}
	i = 0;
	while (i < sim->philo_num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < sim->philo_num)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	free_structs(philo, sim);
	return (0);
}
