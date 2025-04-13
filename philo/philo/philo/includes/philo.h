/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:33:22 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 14:38:42 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <limits.h>

# define SLEEP_SLICE 500
# define DEATH_MONITOR_SLICE 1000
# define CLEAN_FORKS	0x01
# define CLEAN_END_MUTEX	0x02
# define CLEAN_PRINT_MUTEX	0x04
# define CHECK_END if (check_sim_end(sim)) break;

typedef struct s_philo		t_philo;
typedef struct s_simulation	t_simulation;

enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
};

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				owner_id;
}	t_fork;

struct s_simulation
{
	long			philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_to_eat;
	long			start_time;
	int				full_philos;
	bool			sim_end;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	print_mutex;
	t_fork			*forks;
	pthread_t		monitor_thread;
	t_philo			*philo_array;
};

struct s_philo
{
	long			philo_id;
	long			last_meal_time;
	int				eat_count;
	pthread_t		thread;
	t_simulation	*sim_data;
	pthread_mutex_t	meal_mutex;
	int				l_fork;
	int				r_fork;
};

//init.c
int		init_philo(t_simulation *sim, t_philo *philo);
int		init_simulation(t_simulation *sim, \
		const char **argv, t_philo *philo);
int		init_forks_mutex(t_simulation *sim);

//routine.c
bool	everybody_is_full(t_philo *philo, t_simulation *sim);
void	*routine(void *arg);
void	*handle_single_philo(t_philo *philo, t_simulation *sim);
void	*handle_multiple_philo(t_philo *philo, t_simulation *sim);

//eat.c
void	eat(t_philo *philo);

//fork.c
bool	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

//death.c
int		kill_philo(t_philo *philo, t_simulation *sim, long cur_time);
void	*monitor_sim_routine(void *arg);
bool	check_sim_end(t_simulation *sim);

//utils.c
void	free_structs(t_philo *philo, t_simulation *sim);
void	print_status(t_philo *philo, const char *status);

//utils_2.c
long	ft_atol(const char *str);
int		check_args(int argc, const char **args, long *n);

//time.c
long	get_current_time(void);
long	get_relative_time(t_simulation *sim);
void	ft_usleep(long duration_ms, t_simulation *sim);
void	ft_think(t_philo *philo, int befor_begin);

//clean.c
void	cleanup_simulation(t_simulation *sim, int flags);

#endif
