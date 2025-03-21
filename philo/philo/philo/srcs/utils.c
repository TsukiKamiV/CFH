//
//  utils.c
//  philo
//
//  Created by Luyao Xu on 19/12/2024.
//

#include "../includes/philo.h"

long int	ft_atol(const char *str)
{
	long result = 0;
	int sign = 1;
	
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
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
	return result * sign;
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
			pthread_mutex_destroy(&philo[i].meal_mutex);
			i++;
		}
		free (philo);
	}
	if (sim)
	{
		if (sim->forks)
		{
			i = 0;
			while (i < sim->philo_num)
			{
				pthread_mutex_destroy(&sim->forks[i].mutex);
				i++;
			}
			free (sim->forks);
		}
	}
	//if (forks)
		//free (forks);
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

void print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	printf("%ld %li %s\n", get_relative_time(philo->sim_data), philo->philo_id, status);
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
}
