/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luxu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 14:31:20 by luxu              #+#    #+#             */
/*   Updated: 2025/04/12 14:32:48 by luxu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

bool	check_time_params(const char **args)
{
	long	tmp;
	int		i;
	
	i = 2;
	while (i <= 4)
	{
		tmp = ft_atol(args[i]);
		if (tmp == LONG_MAX && ft_strcmp(args[i], "9223372036854775807") != 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	number_limits(int argc, const char **args)
{
	long	a;
	
	a = 0;
	if (argc == 6)
	{
		a = ft_atol(args[5]);
		if (a <= 0 || a >= INT_MAX)
		{
			printf("Wrong must-eat time param\n");
			return (false);
		}
	}
	return (true);
}

static bool	validate_args_format(int argc, const char **args)
{
	int	i;
	
	i = 1;
	while (i < argc)
	{
		if (args[i][0] == '\0' || str_is_num(args[i]) == false)
		{
			printf("Invalid argument\n");
			return (false);
		}
		i++;
	}
	return (true);
}

int	check_args(int argc, const char **args, long *n)
{
	int		i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		return (0);
	}
	*n = ft_atol(args[1]);
	if (*n <= 0 || *n > INT_MAX)
	{
		printf("Invalid philosopher number\n");
		return (0);
	}
	if (number_limits(argc, args) == false)
		return (0);
	if (validate_args_format(argc, args) == false)
		return (0);
	return (1);
}
