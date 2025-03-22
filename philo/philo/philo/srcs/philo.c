//
//  main.c
//  philo
//
//  Created by Luyao Xu on 18/12/2024.
//

#include "../includes/philo.h"

int main(int argc, const char * argv[])
{
	long	num;
	long	i;
	t_philo	*philo;
	t_fork	*forks;
	
	num = ft_atol(argv[1]);
	philo = malloc(sizeof(t_philo) * num);
	forks = malloc(sizeof(t_fork) * num);
	i = 0;
	while (i < num)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		philo[i].philo_id = i + 1;
		philo[i].num_philo = num;
		philo[i].eaten = false;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % num];
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);//create thread for one philo
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	free (philo);
	free (forks);
}
