//
//  philo.h
//  philo
//
//  Created by Luyao Xu on 18/12/2024.
//

#ifndef philo_h
#define philo_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int		philo_id;
	long	num_philo;
	bool 	eaten;
	pthread_t	thread;
	t_fork	*left_fork;
	t_fork	*right_fork;
}		t_philo;

void		*routine(void *arg);
long int	ft_atol(const char *str);

#endif /* philo_h */
