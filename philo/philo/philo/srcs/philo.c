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
	t_simulation	*sim;
	
	//TODO:检查输入的大小限制
	if (check_args(argc, argv) == 0)
		return (1);
	printf("philo num: %s\n", argv[1]);
	printf("time to die: %s\n", argv[2]);
	printf("time to eat: %s\n", argv[3]);
	printf("time to sleep: %s\n", argv[4]);
	if (argc == 6)
		printf("must eat time: %s\n", argv[5]);
	printf("\n");
	
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (1);
	n = ft_atol(argv[1]);
	if (n <= 0 || n > INT_MAX)
	{
		printf("Invalid philosopher number\n");
		return (1);
	}
	sim->philo_num = (int)n;
	philo = malloc(sizeof(t_philo) * sim->philo_num);
	if (!philo)
	{
		free_structs(philo, sim);
		return (1);
	}
	//初始化simulation中其他的变量，如果初始化失败直接结束程序
	if (init_simulation(sim, argv, philo) == 1)
	{
		free (sim);
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
	/**
	 *在执行阶段，多线程程序启动后，各个哲学家线程和监控线程都是并发运行的，但不能保证它们完全同步进入循环。也就是说，哲学家线程在调用 init_philo 时创建并启动，而 monitor
	 *线程是在哲学家线程之后创建的，但由于操作系统线程调度的特性，它们实际上会接近并发执行，
	 *不过各自的启动时机和进入循环的具体时间会有微小差异。这种差异通常不会影响程序逻辑。
	 */
	if (sim->philo_num > 1)
		pthread_create(&sim->monitor_thread, NULL, monitor_sim_routine, sim);
	i = 0;
	while (i < sim->philo_num)
	{
		//printf("joining thread for philo[%ld]\n", philo[i].philo_id);
		pthread_join(philo[i].thread, NULL);
		//printf("END JOINING for philo[%ld]\n", philo[i].philo_id);
		i++;
	}
	if (sim->philo_num > 1)
		pthread_join(sim->monitor_thread, NULL);
	//printf("Death monitor thread joint\n");
	i = 0;
	while (i < sim->philo_num)
	{
		pthread_mutex_destroy(&sim->forks[i].mutex);
		i++;
	}
	free_structs(philo, sim);
	return (0);
}
