//
//  utils.c
//  philo
//
//  Created by Luyao Xu on 19/12/2024.
//

#include "../includes/philo.h"

long	ft_atol(const char *str)
{
	long result = 0;
	int sign = 1;
	
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		   *str == '\r' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+') 
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9') 
	{
		long digit = *str - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (sign == 1) ? LONG_MAX : LONG_MIN;
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

bool	str_is_num(const char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}

void	free_structs(t_philo *philo, t_simulation *sim)
{
	int	i;
	
	if (philo)
	{
		i = 0;
		while (i < sim->philo_num)
		{
			printf("Destroying philo[%d].meal_mutex at %p\n", i, (void *)&philo[i].meal_mutex);
			pthread_mutex_destroy(&philo[i].meal_mutex);
			i++;
		}
		free (philo);
	}
	if (sim)
	{
		if (sim->forks)
		{
			i = 1;
			while (i <= sim->philo_num)
			{
				printf("Destroying sim->forks[%d].mutex at %p\n", i, (void *)&sim->forks[i].mutex);
				pthread_mutex_destroy(&sim->forks[i].mutex);
				i++;
			}
			free (sim->forks);
		}
	}
	printf("Destroying sim->print_mutex at %p\n", (void *)&sim->print_mutex);
	pthread_mutex_destroy(&sim->print_mutex);
	printf("Destroying sim->end_mutex at %p\n", (void *)&sim->end_mutex);
	pthread_mutex_destroy(&sim->end_mutex);
	free (sim);
}

int	check_args(int argc, const char **args)
{
	int		i;
	
	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	while (i < argc)
	{
		//printf("%s\n", args[i]);
		if (args[i][0] == '\0' || str_is_num(args[i]) == false)
		{
			printf("Invalid argument\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int i;
	
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	if (ft_strcmp(status, "Everybody is full!") != 0)
		printf("%ld %li %s\n", get_relative_time(philo->sim_data), philo->philo_id, status);
	else
		printf("%ld %s\n", get_relative_time(philo->sim_data), status);
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
}
