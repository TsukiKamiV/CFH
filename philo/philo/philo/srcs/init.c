//
//  init.c
//  philo
//
//  Created by Luyao Xu on 17/03/2025.
//

#include "../includes/philo.h"

/**
 *@return 1 if fail to create mutex or malloc
 *		  0 on succes
 */
int init_simulation(t_simulation *sim, const char **argv)
{
	sim->time_to_die = ft_atol(argv[2]);
	sim->time_to_eat = ft_atol(argv[3]);
	sim->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] && argv[5][0] != '\0')
		sim->number_of_times_to_eat = ft_atol(argv[5]);
	else
		sim->number_of_times_to_eat = -1;//随后检查如果次数为负数则忽略这一指标？
	sim->sim_end = false;
	sim->full_philos = 0;
	sim->start_time = get_current_time();
	if (pthread_mutex_init(&sim->end_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->end_mutex);
		return (1);
	}
	sim->forks = malloc(sizeof(t_fork) * sim->philo_num);
	if (!sim->forks)
	{
		pthread_mutex_destroy(&sim->end_mutex);
		pthread_mutex_destroy(&sim->print_mutex);
		return (1);
	}
	if (init_forks_mutex(sim) == 1)
		return (1);
	return (0);
}

/**
 *@return 1 if fail to create thread or mutext
 *		  0 on succes
 */

int	init_philo(t_simulation *sim, t_philo *philo, long start_time)
{
	int	i;
	
	if (!philo)
		return (0);
	i = 0;
	while (i < sim->philo_num)
	{
		philo[i].philo_id = i + 1;
		philo[i].last_meal_time = start_time;
		philo[i].eat_count = 0;
		philo[i].sim_data = sim;
		philo[i].l_fork = i;//环形计算下一个index
		philo[i].r_fork = (i + 1) % sim->philo_num;
		//内存泄漏(已修复，待确认）
		if (pthread_mutex_init(&philo[i].meal_mutex, NULL) != 0)//保护last_meal_time和eat_count
			return (1);
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)//这一步实际上同时完成了线程的创建和routine的执行，应该放到外面？？
		{
			while (--i >= 0)
			{
				//如果任意线程创建失败，要回滚已创建的线程
				//是否要destroy上面的锁🔒？=> yes
				pthread_join(philo[i].thread, NULL);
				pthread_mutex_destroy(&philo[i].meal_mutex);
			}
			return (1);//线程创建失败
		}
		i++;
	}
	return (0);//succes
}

/**
 *@return 0 on succes
 *		  1 on failure
 */
int	init_forks_mutex(t_simulation *sim)
{
	int	i;
	int	j;

	i = 0;
	while (i < sim->philo_num)
	{
		if (pthread_mutex_init(&sim->forks[i].mutex, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				//销毁已创建的🔒
				pthread_mutex_destroy(&sim->forks[j].mutex);
				j++;
			}
			free (sim->forks);
			pthread_mutex_destroy(&sim->end_mutex);
			pthread_mutex_destroy(&sim->print_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
