#include "../includes/philo.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
		c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (ft_isspace(*str)) str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (sign == 1) return (LONG_MAX);
			return (LONG_MIN);
		}
		result = result * 10 + (*str - '0');
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
